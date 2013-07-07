#include "FriendsDb.h"

#include <QtSql>

#include "utils/PathUtils.h"
#include "engine/User.h"

#define MY_FRIENDS_TABLE "MY_FRIENDS"
#define USER_ID_COLUMN "USER_ID"
#define PARENT_ID "PARENT_ID"
#define LEVEL_COLUMN "LEVEL"

#define DETAILS_TABLE "DETAILS"
#define COUNTRY_COLUMN "COUNTRY"
#define CITY_COLUMN "CITY"
#define HOME_TOWN_COLUMN "HOMETOWN"
#define TIMEZONE_COLUMN "TIMEZONE"

#define JOINED_TABLE_NAME   MY_FRIENDS_TABLE \
    " LEFT INNER JOIN " DETAILS_TABLE \
    " ON " MY_FRIENDS_TABLE "." USER_ID_COLUMN " = " DETAILS_TABLE "." USER_ID_COLUMN

FriendsDb::FriendsDb(QObject *parent) :
    QObject(parent)
{
    QString path = PathUtils::storageFolder() + "friends.db";


    db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    db->setDatabaseName(path);

    if (!db->open()) {
        qDebug() << db->lastError().text();
    }

    if (!db->tables().contains(MY_FRIENDS_TABLE)) {
        createTables();
    }

}

FriendsDb::~FriendsDb()
{
    db->close();
    delete db;
    db = NULL;
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
        QString str = "CREATE TABLE " DETAILS_TABLE " ("
                      USER_ID_COLUMN " INTEGER PRIMARY KEY, "
                      COUNTRY_COLUMN " TEXT, "
                      CITY_COLUMN " TEXT, "
                      HOME_TOWN_COLUMN " TEXT, "
                      TIMEZONE_COLUMN " INTEGER, "
                      "FOREIGN KEY (" USER_ID_COLUMN ") REFERENCES " MY_FRIENDS_TABLE "(" USER_ID_COLUMN ")"
                      ")";
        result = result && query.exec(str);
    }

    return result;
}

void FriendsDb::storeFriends(const User& user)
{
    QVariantList userIdList;
    QVariantList countryList;
    QVariantList cityList;
    QVariantList homeTownList;
    QVariantList timezoneList;

    for (UserData userData : user.getFriends()) {
        userIdList.push_back(userData.getUserId());
        countryList.push_back(userData.getCountry());
        cityList.push_back(userData.getCity());
        homeTownList.push_back(userData.getHomeTown());
        timezoneList.push_back(userData.getTimezone());
    }

    db->transaction();

    bool success = true;

    {
        QString parentId = QString::number(user.getUserData().getUserId());
        QString level = QString::number(user.getUserData().getLevel() + 1);

        QSqlQuery query("INSERT OR IGNORE INTO " MY_FRIENDS_TABLE
                        " (" USER_ID_COLUMN ", "
                        PARENT_ID ", "
                        LEVEL_COLUMN  ") "
                        " VALUES (?, "
                        + parentId + ", "
                        + level + ")");

        query.addBindValue(userIdList);

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
