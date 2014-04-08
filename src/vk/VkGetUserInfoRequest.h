#ifndef VKGETUSERINFOREQUEST_H
#define VKGETUSERINFOREQUEST_H

#include "engine/GetUserInfoRequest.h"

class VkGetUserInfoRequest : public GetUserInfoRequest
{
    Q_OBJECT
public:
    explicit VkGetUserInfoRequest(const User& user, QObject *parent = 0);

signals:

public slots:

protected: // SocialRequest
    virtual QUrl getRequestUrl(const QString& userId);
    virtual void processReceivedResponse(const QByteArray& response);

};

#endif // VKGETUSERINFOREQUEST_H
