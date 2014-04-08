#ifndef SOCIALREQUESTFACTORY_H
#define SOCIALREQUESTFACTORY_H

#include <memory>
#include "engine/GetFriendsRequest.h"
#include "engine/SocialRequest.h"

class SocialRequestFactory
{
public:
    SocialRequestFactory(std::shared_ptr<AuthManager> authManager)
        : authManager(authManager)
    {
    }

    virtual ~SocialRequestFactory() { }

    virtual std::shared_ptr<SocialRequest> createGetUserInfoRequest(const User& user) = 0;
    virtual std::shared_ptr<SocialRequest> createGetFriendsRequest(const User& user) = 0;

protected:
    std::shared_ptr<SocialRequest> setupRequest(std::shared_ptr<SocialRequest> request)
    {
        request.get()->setAuthManager(authManager);
        return request;
    }

private:
    std::shared_ptr<AuthManager> authManager;

};

#endif // SOCIALREQUESTFACTORY_H
