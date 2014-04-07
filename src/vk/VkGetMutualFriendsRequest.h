#ifndef VKGETMUTUALFRIENDSREQUEST_H
#define VKGETMUTUALFRIENDSREQUEST_H

#include <QObject>
#include "engine/GetMutualFriendsRequest.h"

class VkGetMutualFriendsRequest : public GetMutualFriendsRequest
{
    Q_OBJECT
public:
    explicit VkGetMutualFriendsRequest(const User& sourceUser, const User& targetUser, QObject* parent = 0);

signals:

public slots:

protected: // SocialRequest
    virtual QUrl getRequestUrl(const QString& userId);
    virtual void processReceivedResponse(const QByteArray& response);

};

#endif // VKGETMUTUALFRIENDSREQUEST_H
