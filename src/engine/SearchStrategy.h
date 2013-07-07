#ifndef SEARCHSTRATEGY_H
#define SEARCHSTRATEGY_H

#include <QList>
#include "engine/User.h"

class SearchStrategy
{
public:
    virtual ~SearchStrategy() { }

    virtual void onFriendsReceived(UserList users) = 0;
    virtual UserList getListOfUsersToFetchTheirFriends() = 0;
};

#endif // SEARCHSTRATEGY_H
