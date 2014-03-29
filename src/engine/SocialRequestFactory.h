#ifndef SOCIALREQUESTFACTORY_H
#define SOCIALREQUESTFACTORY_H

#include <memory>
#include "engine/GetFriendsRequest.h"
#include "engine/SocialRequest.h"

class SocialRequestFactory
{
public:
    virtual ~SocialRequestFactory() { }

    virtual std::shared_ptr<SocialRequest> createGetFriendsRequest(const User& user) = 0;
};

#endif // SOCIALREQUESTFACTORY_H
