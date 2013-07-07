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

    virtual void storeUser(const UserData& userData);
    virtual void storeUsers(QList<UserData> users);
    virtual QList<UserData> findMutualFriends();
    virtual QList<UserData> getUserFullChain(int mutualUserId);

private:
    virtual void storeUsers(QList<UserData> users, UserData::UserSide userSide);

    QString getTableForUserSide(UserData::UserSide userSide);
    bool getUserData(int userId, UserData& userData);
    bool getUserData(int userId, UserData::UserSide userSide, UserData& userData);

    QList<UserData> getUserChain(int fromUserId, UserData::UserSide userSide);

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
