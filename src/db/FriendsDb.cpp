#include "FriendsDb.h"

#include <QtSql>

#include "utils/PathUtils.h"

#define MY_FRIENDS_TABLE "MY_FRIENDS"
#define ID_COLUMN "ID"
#define USER_ID_COLUMN "USER_ID"
#define PARENT_ID "PARENT_ID"
#define LEVEL_COLUMN "LEVEL"

FriendsDb::FriendsDb(QObject *parent) :
    QObject(parent)
{
    QString path = PathUtils::storageFolder() + "friends.db";


    _db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    _db->setDatabaseName(path);

    if (!_db->open()) {
        qDebug() << _db->lastError().text();
    }

    if (!_db->tables().contains(MY_FRIENDS_TABLE)) {
        createTables();
    }

}

FriendsDb::~FriendsDb()
{
    _db->close();
    delete _db;
    _db = NULL;
}

bool FriendsDb::createTables()
{
    QSqlQuery query;
    QString str = "CREATE TABLE " MY_FRIENDS_TABLE " ("
                  ID_COLUMN " INTEGER PRIMARY KEY ASC, "
                  USER_ID_COLUMN " TEXT UNIQUE, "
                  PARENT_ID " TEXT, "
                  LEVEL_COLUMN " INTEGER NOT NULL"
                  ")";
    return query.exec(str);
}

void FriendsDb::storeFriends(QStringList friendsList, QString parentId, int level)
{
    QVariantList userIdList;

    for (QString item : friendsList) {
        userIdList.push_back(item);
    }

    _db->transaction();

    QString levelStr = QString::number(level);

    QSqlQuery query("INSERT OR IGNORE INTO " MY_FRIENDS_TABLE
                    " (" USER_ID_COLUMN ", "
                    PARENT_ID ", "
                    LEVEL_COLUMN ") "
                    " VALUES (?, "
                    + parentId + ", "
                    + levelStr + ")");

    query.addBindValue(userIdList);

    bool success = query.execBatch();

    if (success) {
        _db->commit();
    } else {
        _db->rollback();
    }
}
