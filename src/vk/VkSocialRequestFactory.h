#ifndef VKSOCIALREQUESTFACTORY_H
#define VKSOCIALREQUESTFACTORY_H

#include "engine/SocialRequestFactory.h"

class VkSocialRequestFactory : public SocialRequestFactory
{
public:
    VkSocialRequestFactory();

public: // SocialRequestFactory
    virtual std::shared_ptr<SocialRequest> createGetFriendsRequest(const User& user);
};

#endif // VKSOCIALREQUESTFACTORY_H
