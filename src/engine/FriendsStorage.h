#ifndef FRIENDSSTORAGE_H
#define FRIENDSSTORAGE_H

#include <QStringList>

class User;

class FriendsStorage
{
public:
    virtual ~FriendsStorage() { }

    virtual void storeFriends(const User& user) = 0;
};

#endif // FRIENDSSTORAGE_H
