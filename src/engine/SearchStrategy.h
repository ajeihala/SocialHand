#ifndef SEARCHSTRATEGY_H
#define SEARCHSTRATEGY_H

#include <QList>
#include "engine/User.h"

class SearchStrategy
{
public:
    virtual ~SearchStrategy() { }

    virtual void onFriendsReceived(QList<UserData> users) = 0;
    virtual QList<UserData> getListOfUsersToFetchTheirFriends() = 0;
};

#endif // SEARCHSTRATEGY_H
