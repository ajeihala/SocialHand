#include "Engine.h"

#include "engine/AuthManager.h"
#include "engine/SocialRequestFactory.h"
#include "engine/GetFriendsRequest.h"

#include <QDebug>

Engine::Engine(AuthManager* auth, SocialRequestFactory* socialRequest, QObject* parent) :
    QObject(parent),
    _authManager(auth),
    _socialRequest(socialRequest)
{
}

Engine::Engine(QObject* parent) :
    QObject(parent),
    _authManager(nullptr),
    _socialRequest(nullptr)
{
}

void Engine::start()
{
    QString initialUserId = _authManager->getOriginatorUserId();

    GetFriendsRequest* friendsRequest = _socialRequest->createGetFriendsRequest();
    connect(friendsRequest, SIGNAL(friendsRequestFinished(GetFriendsRequest*,QString,QStringList)),
            this, SLOT(onGetFriendsRequestFinished(GetFriendsRequest*,QString,QStringList)));

    friendsRequest->startRequest(initialUserId);
}

void Engine::onGetFriendsRequestFinished(GetFriendsRequest* request, QString userId, QStringList friendsList)
{
    qDebug() << "List for user id: " << userId << " : " << friendsList;
    request->deleteLater();
}


