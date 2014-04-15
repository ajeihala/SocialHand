#ifndef GETUSERINFOREQUEST_H
#define GETUSERINFOREQUEST_H

#include "engine/SocialRequest.h"
#include "engine/UserInfo.h"

class GetUserInfoRequest: public SocialRequest {
public:
    explicit GetUserInfoRequest(const User& user, QObject *parent = 0)
        : SocialRequest(SocialRequest::Type::kGetUserInfo, user, parent)
    {   }

public:
    UserInfo getUserInfo() const {
        return userInfo;
    }

protected:
    void setUserInfo(const UserInfo& userInfo) {
        this->userInfo = userInfo;
    }

private:
    UserInfo userInfo;

};

#endif // GETUSERINFOREQUEST_H
