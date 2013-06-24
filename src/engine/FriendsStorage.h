#ifndef FRIENDSSTORAGE_H
#define FRIENDSSTORAGE_H

#include <QStringList>

class FriendsStorage
{
public:
    virtual ~FriendsStorage() { }

    virtual void storeFriends(QStringList friendsList, QString parentId, int level) = 0;
};

#endif // FRIENDSSTORAGE_H
