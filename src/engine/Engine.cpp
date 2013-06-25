#include "Engine.h"

#include "engine/AuthManager.h"
#include "engine/SocialRequestFactory.h"
#include "engine/GetFriendsRequest.h"
#include "engine/FriendsStorage.h"

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
    QString initialUserId = _authManager->getOriginatorUserId();

    _storage->storeFriends(QStringList() << initialUserId, "", 0);

    startRequests(QStringList() << initialUserId, 1);
}

void Engine::startRequests(QStringList userIdList, int level)
{
    _requestsQueue.startRequests(userIdList, level);
}

void Engine::requestFinished(QString parentId, QStringList friendsList, int level)
{
    qDebug() << "List for user id: " << parentId << " : " << friendsList;

    _storage->storeFriends(friendsList, parentId, level);

    ++level;
    if (level < 3) {
        startRequests(friendsList, level);
    }
}
