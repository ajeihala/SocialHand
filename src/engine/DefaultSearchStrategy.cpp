#include "DefaultSearchStrategy.h"

DefaultSearchStrategy::DefaultSearchStrategy(QObject *parent) :
    QObject(parent)
{
}

void DefaultSearchStrategy::onFriendsReceived(UserList users)
{
    this->users = users;
}

UserList DefaultSearchStrategy::getListOfUsersToFetchTheirFriends()
{
    UserList result;

    result = users;
    users.clear();

    return result;
}
