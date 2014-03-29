#ifndef GETFRIENDSREQUEST_H
#define GETFRIENDSREQUEST_H

#include <QString>
#include <QStringList>

#include "engine/SocialRequest.h"

class GetFriendsRequest : public SocialRequest
{
    Q_OBJECT
public:
    virtual ~GetFriendsRequest() { }
    GetFriendsRequest(const User& user, QObject* parent = 0)
        : SocialRequest(SocialRequest::Type::kGetFriends, user, parent)
    { }

public:
    virtual const UserList& getFriendsList() = 0;
};

#endif // GETFRIENDSREQUEST_H
