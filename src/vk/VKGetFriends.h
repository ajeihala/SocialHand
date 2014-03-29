#ifndef VKGETFRIENDS_H
#define VKGETFRIENDS_H

#include <QObject>
#include "engine/GetFriendsRequest.h"


class VKGetFriends : public GetFriendsRequest
{
    Q_OBJECT
public:
    explicit VKGetFriends(const User& user, QObject* parent = 0);
    
public: // GetFriendsRequest
    const UserList& getFriendsList();

protected: // SocialRequest
    virtual QUrl getRequestUrl(const QString& userId);
    virtual void processReceivedResponse(const QByteArray& response);

private:
    UserList userList;

};

#endif // VKGETFRIENDS_H
