#ifndef VKGETFRIENDSREQUEST_H
#define VKGETFRIENDSREQUEST_H

#include <QObject>
#include "engine/GetFriendsRequest.h"


class VKGetFriendsRequest : public GetFriendsRequest
{
    Q_OBJECT
public:
    explicit VKGetFriendsRequest(const User& user, QObject* parent = 0);
    
public: // GetFriendsRequest
    const UserList& getFriendsList();

protected: // SocialRequest
    virtual QUrl getRequestUrl(const QString& userId);
    virtual void processReceivedResponse(const QByteArray& response);

private:
    UserList userList;

};

#endif // VKGETFRIENDSREQUEST_H
