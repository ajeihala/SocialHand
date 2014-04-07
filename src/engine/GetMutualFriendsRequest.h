#ifndef GETMUTUALFRIENDSREQUEST_H
#define GETMUTUALFRIENDSREQUEST_H

#include <QString>
#include <QStringList>

#include "engine/SocialRequest.h"

class GetMutualFriendsRequest : public SocialRequest
{
    Q_OBJECT
public:
    virtual ~GetMutualFriendsRequest() { }
    GetMutualFriendsRequest(const User& sourceUser, const User& targetUser, QObject* parent = 0)
        : SocialRequest(SocialRequest::Type::kGetMutualFriends, targetUser, parent)
        , sourceUser(sourceUser)
    { }

public:

    const User& getSourceUser() const {
        return sourceUser;
    }

private:
    const User& sourceUser;
};

#endif // GETMUTUALFRIENDSREQUEST_H
