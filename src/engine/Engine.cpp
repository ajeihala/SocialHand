#include "Engine.h"

#include "engine/AuthManager.h"
#include "engine/SocialRequestFactory.h"
#include "engine/GetFriendsRequest.h"
#include "engine/FriendsStorage.h"
#include "engine/User.h"
#include "engine/SearchStrategy.h"

#include <QDebug>

Engine::Engine(AuthManager* auth, SocialRequestFactory* socialRequestFactory, FriendsStorage* storage, SearchStrategy* searchStrategy, QObject* parent)
    : QObject(parent)
    , authManager(auth)
    , socialRequestFactory(socialRequestFactory)
    , storage(storage)
    , searchStrategy(searchStrategy)
    , requestsQueue(*this, *socialRequestFactory)
{
}

Engine::Engine(QObject* parent)
    : Engine(nullptr, nullptr, nullptr, nullptr, parent)
{
}

void Engine::start(QString target)
{
    storage->clearAll();

    int initialUserId = authManager->getOriginatorUserId();
    targetUserId = target.toInt();

    User initialUser(initialUserId, 0, 0, User::UserSide::kMyFriend);
    storage->storeUser(initialUser);

    User targetUser(targetUserId, 0, 0, User::UserSide::kTargetFriend);
    storage->storeUser(targetUser);

    processSearchIteration(UserList() << initialUser << targetUser);
}

void Engine::startRequests(UserList usersList)
{
    requestsQueue.startRequests(usersList);
}

void Engine::processSearchIteration(UserList users)
{
    UserList mutialFriends = storage->findMutualFriends();

    if (mutialFriends.isEmpty()) {
        searchStrategy->onFriendsReceived(users);

        UserList listToFetch = searchStrategy->getListOfUsersToFetchTheirFriends();

        if (!users.isEmpty() && users.at(0).getLevel() < 2) {
            startRequests(listToFetch);
        }
    } else {
        requestsQueue.cancellAll();
        UserList chain = storage->getUserFullChain(mutialFriends.at(0).getUserId());
        qDebug() << "Found (" << mutialFriends.count() << ") !!! Friends chain: " << chain;
    }
}

void Engine::requestFinished(UserList users)
{
    storage->storeUsers(users);
    processSearchIteration(users);
}
