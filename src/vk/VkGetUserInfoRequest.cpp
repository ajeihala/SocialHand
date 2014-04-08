#include "VkGetUserInfoRequest.h"

VkGetUserInfoRequest::VkGetUserInfoRequest(const User& user, QObject *parent) :
    GetUserInfoRequest(user, parent)
{
}

QUrl VkGetUserInfoRequest::getRequestUrl(const QString& userId)
{
    QString fields("uid,first_name,last_name,nickname,screen_name,sex,birthdate,city,country,timezone,photo,photo_medium,photo_big,has_mobile,rate,contacts,education,online");
    QString nameCase("nom");
    return QUrl(QString("https://api.vk.com/method/users.get?uids=%1&fields=%2&name_case=%3")
                .arg(userId)
                .arg(fields)
                .arg(nameCase));
}

void VkGetUserInfoRequest::processReceivedResponse(const QByteArray& response)
{
    qDebug() << response;
}
