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

void Engine::start(QString targetUserId)
{
    storage->clearAll();

    int initialUserId = authManager->getOriginatorUserId();

    User initialUser(initialUserId, 0, 0, User::UserSide::kMyFriend);
//    storage->storeUser(initialUser);

    User targetUser(targetUserId.toInt(), 0, 0, User::UserSide::kTargetFriend);
//    storage->storeUser(targetUser);

    processSearchIteration(UserList() << initialUser << targetUser);
}

void Engine::startRequests(const QList<std::shared_ptr<SocialRequest> >& requests)
{
    requestsQueue.startRequests(requests);
}

void Engine::processSearchIteration(UserList users)
{
    storage->storeUsers(users);

    UserList mutialFriends = storage->findMutualFriends();

    if (mutialFriends.isEmpty()) {
        searchStrategy->onFriendsReceived(users);

        UserList listToFetch = searchStrategy->getListOfUsersToFetchTheirFriends();
        auto friendsRequests = prepareGetFriendsRequests(listToFetch);

        if (!users.isEmpty() && users.at(0).getLevel() < 2) {
            startRequests(friendsRequests);
        }
    } else {
        requestsQueue.cancelAll();
        UserList chain = storage->getUserFullChain(mutialFriends.at(0).getUserId());
        qDebug() << "Found (" << mutialFriends.count() << ") !!! Friends chain: " << chain;
    }
}

QList<std::shared_ptr<SocialRequest> > Engine::prepareGetFriendsRequests(const UserList& list)
{
    QList<std::shared_ptr<SocialRequest> > result;

    for (User user : list) {
        result.append(socialRequestFactory->createGetFriendsRequest(user));
    }

    return result;
}

void Engine::handleFinishedRequest(SocialRequest* request)
{
    switch (request->getType()) {
    case SocialRequest::Type::kGetFriends: {
        GetFriendsRequest* getFriendsRequest = static_cast<GetFriendsRequest*>(request);
        const UserList friendsList = getFriendsRequest->getFriendsList();
        processSearchIteration(friendsList);
    }
        break;

    default:
        break;
    }
}

void Engine::requestFinished(SocialRequest* request)
{
    handleFinishedRequest(request);
}
