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

    virtual void storeUser(const User& user) = 0;
    virtual void storeUsers(UserList users) = 0;
    virtual UserList findMutualFriends() = 0;
    virtual UserList getUserFullChain(int mutualUserId) = 0;
};

#endif // FRIENDSSTORAGE_H
