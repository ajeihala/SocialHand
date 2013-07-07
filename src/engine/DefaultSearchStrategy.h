#ifndef DEFAULTSEARCHSTRATEGY_H
#define DEFAULTSEARCHSTRATEGY_H

#include <QObject>

#include "engine/SearchStrategy.h"

class DefaultSearchStrategy : public QObject, public SearchStrategy
{
    Q_OBJECT
public:
    explicit DefaultSearchStrategy(QObject *parent = 0);
    
public: // SearchStrategy
    virtual void onFriendsReceived(UserList users);
    virtual UserList getListOfUsersToFetchTheirFriends();


private:
    UserList users;
};

#endif // DEFAULTSEARCHSTRATEGY_H
