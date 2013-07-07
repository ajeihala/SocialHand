#ifndef SEARCHSTRATEGY_H
#define SEARCHSTRATEGY_H

#include <QList>
#include "engine/User.h"

class SearchStrategy
{
public:
    virtual ~SearchStrategy() { }

    virtual void onFriendsReceived(const User& user) = 0;
    virtual QList<UserData> getListOfUsersToFetchTheirFriends() = 0;
};

#endif // SEARCHSTRATEGY_H
