#ifndef FRIENDSDB_H
#define FRIENDSDB_H

#include <QObject>

#include "engine/FriendsStorage.h"

class QSqlDatabase;

class FriendsDb : public QObject, public FriendsStorage
{
    Q_OBJECT
public:
    explicit FriendsDb(QObject *parent = 0);
    virtual ~FriendsDb();
    
public: // FrindsStorage
    virtual void clearAll();

    virtual void storeInitialUser(const UserData& userData);
    virtual void storeFriends(const User& user);
    virtual QList<UserData> findMutualFriends();

private:
    QString getTableForUserSide(UserData::UserSide userSide);
    bool getUserData(int userId, UserData& userData);
    bool getUserData(int userId, UserData::UserSide userSide, UserData& userData);

    QList<UserData> getUserChain(int fromUserId, UserData::UserSide userSide);

private:
    void initDb();
    void closeDb();
    bool createTables();
    QString getDbPath();

private:
    QSqlDatabase* db;
    
};

#endif // FRIENDSDB_H
