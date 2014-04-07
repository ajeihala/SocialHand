#include "vk/VkGetMutualFriendsRequest.h"

VkGetMutualFriendsRequest::VkGetMutualFriendsRequest(const User& sourceUser, const User& targetUser, QObject *parent)
    : GetMutualFriendsRequest(sourceUser, targetUser, parent)
{
}

QUrl VkGetMutualFriendsRequest::getRequestUrl(const QString& userId)
{
    QString token = getAuthManager()->getAccessToken();
    return QUrl(QString("https://api.vk.com/method/friends.getMutual?target_uid=%1&source_uid=%2&access_token=%3")
                .arg(userId)
                .arg(getSourceUser().getUserId())
                .arg(token));
}

void VkGetMutualFriendsRequest::processReceivedResponse(const QByteArray& response)
{
    qDebug() << response;
}
