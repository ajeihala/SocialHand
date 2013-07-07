#include "DefaultSearchStrategy.h"

DefaultSearchStrategy::DefaultSearchStrategy(QObject *parent) :
    QObject(parent)
{
}

void DefaultSearchStrategy::onFriendsReceived(const User& user)
{
    if (!user.getFriends().isEmpty()) {
        users = user.getFriends();
    } else {
        if (user.getUserData().getLevel() == 0) {
            users = QList<UserData>() << user.getUserData();
        }
    }
}

QList<UserData> DefaultSearchStrategy::getListOfUsersToFetchTheirFriends()
{
    QList<UserData> result;

    result = users;
    users.clear();

    return result;
}
