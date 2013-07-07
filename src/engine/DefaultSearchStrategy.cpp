#include "DefaultSearchStrategy.h"

DefaultSearchStrategy::DefaultSearchStrategy(QObject *parent) :
    QObject(parent)
{
}

void DefaultSearchStrategy::onFriendsReceived(QList<UserData> users)
{
    this->users = users;
}

QList<UserData> DefaultSearchStrategy::getListOfUsersToFetchTheirFriends()
{
    QList<UserData> result;

    result = users;
    users.clear();

    return result;
}
