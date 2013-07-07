#include "FriendsDb.h"

#include <QtSql>

#include "utils/PathUtils.h"
#include "engine/User.h"

#define MY_FRIENDS_TABLE "MY_FRIENDS"
#define TARGET_FRIENDS_TABLE "TARGET_FRIENDS"
#define USER_ID_COLUMN "USER_ID"
#define PARENT_ID "PARENT_ID"
#define LEVEL_COLUMN "LEVEL"

#define DETAILS_TABLE "DETAILS"
#define COUNTRY_COLUMN "COUNTRY"
#define CITY_COLUMN "CITY"
#define HOME_TOWN_COLUMN "HOMETOWN"
#define TIMEZONE_COLUMN "TIMEZONE"

FriendsDb::FriendsDb(QObject *parent) :
    QObject(parent)
{
    initDb();
}

FriendsDb::~FriendsDb()
{
    closeDb();
}

void FriendsDb::initDb()
{
    QString path = getDbPath();

    db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    db->setDatabaseName(path);

    if (!db->open()) {
        qDebug() << db->lastError().text();
    }

    if (!db->tables().contains(MY_FRIENDS_TABLE)) {
        createTables();
    }

}

void FriendsDb::closeDb()
{
    db->close();
    delete db;
    db = NULL;
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
}

QString FriendsDb::getDbPath()
{
    return PathUtils::storageFolder() + "friends.db";
}

bool FriendsDb::createTables()
{
    bool result = false;

    {
        QSqlQuery query;
        QString str = "CREATE TABLE " MY_FRIENDS_TABLE " ("
                      USER_ID_COLUMN " INTEGER PRIMARY KEY, "
                      PARENT_ID " INTEGER, "
                      LEVEL_COLUMN " INTEGER NOT NULL"
                      ")";
        result = query.exec(str);
    }

    {
        QSqlQuery query;
        QString str = "CREATE TABLE " TARGET_FRIENDS_TABLE " ("
                      USER_ID_COLUMN " INTEGER PRIMARY KEY, "
                      PARENT_ID " INTEGER, "
                      LEVEL_COLUMN " INTEGER NOT NULL"
                      ")";
        result = query.exec(str);
    }

    {
        QSqlQuery query;
        QString str = "CREATE TABLE " DETAILS_TABLE " ("
                      USER_ID_COLUMN " INTEGER PRIMARY KEY, "
                      COUNTRY_COLUMN " TEXT, "
                      CITY_COLUMN " TEXT, "
                      HOME_TOWN_COLUMN " TEXT, "
                      TIMEZONE_COLUMN " INTEGER "
                      ")";
        result = result && query.exec(str);
    }

    return result;
}

void FriendsDb::clearAll()
{
    closeDb();
    QFile::remove(getDbPath());
    initDb();
}

void FriendsDb::storeUser(const UserData& userData)
{
    storeUsers(QList<UserData>() << userData);
}

void FriendsDb::storeUsers(QList<UserData> users)
{
    QList<UserData> myFriends;
    myFriends.reserve(users.count());

    QList<UserData> targetFriends;
    targetFriends.reserve(users.count());

    for (UserData userData : users) {
        if (userData.getUserSide() == UserData::UserSide::kMyFriend) {
            myFriends.append(userData);
        } else {
            targetFriends.append(userData);
        }
    }

    storeUsers(myFriends, UserData::UserSide::kMyFriend);
    storeUsers(targetFriends, UserData::UserSide::kTargetFriend);
}

void FriendsDb::storeUsers(QList<UserData> users, UserData::UserSide userSide)
{
    if (users.isEmpty()) {
        return;
    }

    QVariantList userIdList;
    QVariantList parentIdList;
    QVariantList levelList;
    QVariantList countryList;
    QVariantList cityList;
    QVariantList homeTownList;
    QVariantList timezoneList;

    for (UserData userData : users) {
        userIdList.push_back(userData.getUserId());
        parentIdList.push_back(userData.getParentId());
        levelList.push_back(userData.getLevel());
        countryList.push_back(userData.getCountry());
        cityList.push_back(userData.getCity());
        homeTownList.push_back(userData.getHomeTown());
        timezoneList.push_back(userData.getTimezone());
    }

    db->transaction();

    bool success = true;

    {
        QString tableToInsert = getTableForUserSide(userSide);

        QSqlQuery query("INSERT OR IGNORE INTO " + tableToInsert +
                        " (" USER_ID_COLUMN ", "
                        PARENT_ID ", "
                        LEVEL_COLUMN  ") "
                        " VALUES (?, ?, ?)");

        query.addBindValue(userIdList);
        query.addBindValue(parentIdList);
        query.addBindValue(levelList);

        success = success && query.execBatch();

    }

    {
        QSqlQuery query("INSERT OR IGNORE INTO " DETAILS_TABLE
                        " (" USER_ID_COLUMN ", "
                        COUNTRY_COLUMN ", "
                        CITY_COLUMN ", "
                        HOME_TOWN_COLUMN ", "
                        TIMEZONE_COLUMN ") "
                        " VALUES (?, ?, ?, ?, ?)"
                        );

        query.addBindValue(userIdList);
        query.addBindValue(countryList);
        query.addBindValue(cityList);
        query.addBindValue(homeTownList);
        query.addBindValue(timezoneList);

        success = success && query.execBatch();

    }

    if (success) {
        db->commit();
    } else {
        db->rollback();
    }
}

QList<UserData> FriendsDb::findMutualFriends()
{
    QList<UserData> mutualFriends;

    QSqlQuery query("SELECT " MY_FRIENDS_TABLE "." USER_ID_COLUMN " FROM "
                    MY_FRIENDS_TABLE " JOIN " TARGET_FRIENDS_TABLE
                    " ON " MY_FRIENDS_TABLE "." USER_ID_COLUMN
                    " = " TARGET_FRIENDS_TABLE "." USER_ID_COLUMN);

    query.exec();

    int userIdField = query.record().indexOf(USER_ID_COLUMN);

    QList<int> userIds;

    while (query.next()) {
        int id = query.value(userIdField).toInt();
        userIds.append(id);
    }

    for (int userId : userIds) {
        UserData userData;
        if (getUserData(userId, userData)) {
            mutualFriends.append(userData);
        }
    }

    return mutualFriends;
}

QString FriendsDb::getTableForUserSide(UserData::UserSide userSide)
{
    return userSide == UserData::UserSide::kMyFriend ? MY_FRIENDS_TABLE
                                                     : TARGET_FRIENDS_TABLE;
}

bool FriendsDb::getUserData(int userId, UserData& userData)
{
    return getUserData(userId, UserData::UserSide::kMyFriend, userData) ||
            getUserData(userId, UserData::UserSide::kTargetFriend, userData);
}

bool FriendsDb::getUserData(int userId, UserData::UserSide userSide, UserData& userData)
{
    bool result = false;

    QString table = getTableForUserSide(userSide);

    QSqlQuery query("SELECT * FROM "
                    + table + " JOIN " DETAILS_TABLE
                    " ON " + table + "." USER_ID_COLUMN
                    " = " DETAILS_TABLE "." USER_ID_COLUMN
                    " WHERE " + table + "." USER_ID_COLUMN
                    " = " + QString::number(userId));

    query.exec();

    int userIdField = query.record().indexOf(USER_ID_COLUMN);
    int parentIdField = query.record().indexOf(PARENT_ID);
    int levelField = query.record().indexOf(LEVEL_COLUMN);
    int countryField = query.record().indexOf(COUNTRY_COLUMN);
    int cityField = query.record().indexOf(CITY_COLUMN);
    int homeTownField = query.record().indexOf(HOME_TOWN_COLUMN);
    int timeZoneField = query.record().indexOf(TIMEZONE_COLUMN);

    if (query.next()) {
        userData.setUserSide(userSide);
        userData.setUserId(query.value(userIdField).toInt());
        userData.setParentId(query.value(parentIdField).toInt());
        userData.setLevel(query.value(levelField).toInt());
        userData.setCountry(query.value(countryField).toString());
        userData.setCity(query.value(cityField).toString());
        userData.setHomeTown(query.value(homeTownField).toString());
        userData.setTimezone(query.value(timeZoneField).toInt());

        result = true;
    }

    return result;
}

QList<UserData> FriendsDb::getUserChain(int fromUserId, UserData::UserSide userSide)
{
    QList<UserData> result;

    UserData userData;
    int nextId = fromUserId;
    int level = 0;

    do {
        if (getUserData(nextId, userSide, userData)) {
            result.append(userData);

            nextId = userData.getParentId();
            level = userData.getLevel();
        }
    } while (level > 0);

    return result;
}

QList<UserData> FriendsDb::getUserFullChain(int mutualUserId)
{
    QList<UserData> result;

    QList<UserData> myFriendsChain = reverse(getUserChain(mutualUserId, UserData::UserSide::kMyFriend));
    QList<UserData> targetFriendsChain = getUserChain(mutualUserId, UserData::UserSide::kTargetFriend);
    if (!targetFriendsChain.isEmpty()) {
        targetFriendsChain.removeFirst();
    }

    result = myFriendsChain;
    result.append(targetFriendsChain);
    return result;
}

