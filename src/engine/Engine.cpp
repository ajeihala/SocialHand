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

    UserData initialUser(initialUserId, 0, UserData::UserSide::kMyFriend);
    storage->storeInitialUser(initialUser);

    UserData targetUser(targetUserId, 0, UserData::UserSide::kTargetFriend);
    storage->storeInitialUser(targetUser);

    processSearchIteration(initialUser);
}

void Engine::startRequests(QList<UserData> usersList)
{
    requestsQueue.startRequests(usersList);
}

void Engine::processSearchIteration(const User& user)
{
    QList<UserData> mutialFriends = storage->findMutualFriends();

    if (mutialFriends.isEmpty()) {
        searchStrategy->onFriendsReceived(user);

        QList<UserData> listToFetch = searchStrategy->getListOfUsersToFetchTheirFriends();

        if (user.getUserData().getLevel() < 2) {
            startRequests(listToFetch);
        }
    } else {
        requestsQueue.cancellAll();
        qDebug() << "Found (" << mutialFriends.count() << ") !!! Mutial friend: " << mutialFriends.at(0).getUserId();
    }
}

void Engine::requestFinished(const User& user)
{
    storage->storeFriends(user);
    processSearchIteration(user);
}
