#include "Engine.h"

#include "engine/AuthManager.h"
#include "engine/SocialRequestFactory.h"
#include "engine/GetFriendsRequest.h"
#include "engine/FriendsStorage.h"
#include "engine/User.h"

#include <QDebug>

Engine::Engine(AuthManager* auth, SocialRequestFactory* socialRequestFactory, FriendsStorage* storage, QObject* parent)
    : QObject(parent)
    , _authManager(auth)
    , _socialRequestFactory(socialRequestFactory)
    , _storage(storage)
    , _requestsQueue(*this, *socialRequestFactory)
{
}

Engine::Engine(QObject* parent)
    : Engine(nullptr, nullptr, nullptr, parent)
{
}

void Engine::start()
{
    int initialUserId = _authManager->getOriginatorUserId();

    UserData initialUser(initialUserId, 0);
    _storage->storeFriends(User(initialUser));

    startRequests(QList<UserData>() << initialUser);
}

void Engine::startRequests(QList<UserData> usersList)
{
    _requestsQueue.startRequests(usersList);
}

void Engine::requestFinished(const User& user)
{
//    qDebug() << "List for user id: " << user.userData.userId << " : " << user.friends;

    _storage->storeFriends(user);

    if (user.getUserData().getLevel() < 2) {
        startRequests(user.getFriends());
    }
}
