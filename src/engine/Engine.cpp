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

    UserData initialUser(initialUserId, 0, 0, UserData::UserSide::kMyFriend);
    storage->storeUser(initialUser);

    UserData targetUser(targetUserId, 0, 0, UserData::UserSide::kTargetFriend);
    storage->storeUser(targetUser);

    processSearchIteration(QList<UserData>() << initialUser);
}

void Engine::startRequests(QList<UserData> usersList)
{
    requestsQueue.startRequests(usersList);
}

void Engine::processSearchIteration(QList<UserData> users)
{
    QList<UserData> mutialFriends = storage->findMutualFriends();

    if (mutialFriends.isEmpty()) {
        searchStrategy->onFriendsReceived(users);

        QList<UserData> listToFetch = searchStrategy->getListOfUsersToFetchTheirFriends();

        if (!users.isEmpty() && users.at(0).getLevel() < 2) {
            startRequests(listToFetch);
        }
    } else {
        requestsQueue.cancellAll();
        QList<UserData> chain = storage->getUserFullChain(mutialFriends.at(0).getUserId());
        qDebug() << "Found (" << mutialFriends.count() << ") !!! Friends chain: " << chain;
    }
}

void Engine::requestFinished(QList<UserData> users)
{
    storage->storeUsers(users);
    processSearchIteration(users);
}
