#ifndef GETUSERINFOREQUEST_H
#define GETUSERINFOREQUEST_H

#include "engine/SocialRequest.h"

class GetUserInfoRequest: public SocialRequest {
public:
    explicit GetUserInfoRequest(const User& user, QObject *parent = 0)
        : SocialRequest(SocialRequest::Type::kGetUserInfo, user, parent)
    {   }

};

#endif // GETUSERINFOREQUEST_H
