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

    virtual void storeUser(const User& user);
    virtual void storeUsers(UserList users);
    virtual UserList findMutualFriends();
    virtual UserList getUserFullChain(int mutualUserId);

private:
    virtual void storeUsers(UserList users, User::UserSide userSide);

    QString getTableForUserSide(User::UserSide userSide);
    bool getUser(int userId, User& user);
    bool getUser(int userId, User::UserSide userSide, User& user);

    UserList getUserChain(int fromUserId, User::UserSide userSide);

    template <typename T>
    QList<T> reverse(const QList<T>& list) {
        QList<T> result;
        result.reserve(list.size());
        std::reverse_copy(list.begin(), list.end(), std::back_inserter(result));
        return result;
    }

private:
    void initDb();
    void closeDb();
    bool createTables();
    QString getDbPath();

private:
    QSqlDatabase* db;
    
};

#endif // FRIENDSDB_H
