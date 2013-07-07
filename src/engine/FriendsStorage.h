#ifndef FRIENDSSTORAGE_H
#define FRIENDSSTORAGE_H

#include <QList>

#include "engine/User.h"

class User;

class FriendsStorage
{
public:
    virtual ~FriendsStorage() { }

    virtual void clearAll() = 0;

    virtual void storeUser(const UserData& userData) = 0;
    virtual void storeUsers(QList<UserData> users) = 0;
    virtual QList<UserData> findMutualFriends() = 0;
    virtual QList<UserData> getUserFullChain(int mutualUserId) = 0;
};

#endif // FRIENDSSTORAGE_H
