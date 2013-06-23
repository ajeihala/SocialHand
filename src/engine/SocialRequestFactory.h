#ifndef SOCIALREQUESTFACTORY_H
#define SOCIALREQUESTFACTORY_H

#include "engine/GetFriendsRequest.h"

class SocialRequestFactory
{
public:
    virtual ~SocialRequestFactory() { }

    virtual GetFriendsRequest* createGetFriendsRequest() = 0;
};

#endif // SOCIALREQUESTFACTORY_H
