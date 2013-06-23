#ifndef VKSOCIALREQUESTFACTORY_H
#define VKSOCIALREQUESTFACTORY_H

#include "engine/SocialRequestFactory.h"

class VkSocialRequestFactory : public SocialRequestFactory
{
public:
    VkSocialRequestFactory();

public: // SocialRequestFactory
    virtual GetFriendsRequest* createGetFriendsRequest();
};

#endif // VKSOCIALREQUESTFACTORY_H
