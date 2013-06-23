#include "Engine.h"

#include "engine/AuthManager.h"
#include "engine/SocialRequest.h"

#include <vk/VKGetFriends.h>

Engine::Engine(AuthManager* auth, SocialRequest* socialRequest, QObject* parent) :
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
    QString initialUserId = "42560101";//_authManager->getOriginatorUserId();
    VKGetFriends* request = new VKGetFriends(initialUserId, this);
}
