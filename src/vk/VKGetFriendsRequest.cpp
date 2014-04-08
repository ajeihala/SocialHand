#include "VKGetFriendsRequest.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QStringList>
#include <QVariantList>

#include "engine/User.h"

VKGetFriendsRequest::VKGetFriendsRequest(const User& user, QObject *parent) :
    GetFriendsRequest(user, parent)
{
}

const UserList& VKGetFriendsRequest::getFriendsList()
{
    return userList;
}

QUrl VKGetFriendsRequest::getRequestUrl(const QString& userId)
{
    return QUrl(QString("https://api.vk.com/method/friends.get?user_id=%1&fields=country,city,home_town,timezone").arg(userId));
}

void VKGetFriendsRequest::processReceivedResponse(const QByteArray& response)
{
    QJsonDocument json = QJsonDocument::fromJson(response);

    QJsonObject obj = json.object();
    QJsonValue value = obj.value("response");
    QJsonArray array = value.toArray();

    UserList friendsList;

    int friendsLevel = getUser().getLevel() + 1;
    User::UserSide userSide = getUser().getUserSide();

    for (QJsonValue value : array) {
        QJsonObject object = value.toObject();

        bool isDeactivated = object.value("deactivated").type() != QJsonValue::Undefined;

        if (!isDeactivated) {
            QJsonValue userIdValue = object.value("user_id");
            QJsonValue countryValue = object.value("country");
            QJsonValue cityValue = object.value("city");
            QJsonValue homeTown = object.value("home_town");
            QJsonValue timeZoneValue = object.value("timezone");

            User data(userIdValue.toDouble(), getUser().getUserId(), friendsLevel, userSide);
            data.setCountry(countryValue.toString());
            data.setCity(cityValue.toString());
            data.setHomeTown(homeTown.toString());
            data.setTimezone(timeZoneValue.toDouble());
            friendsList.append(data);
        }
    }

    userList = friendsList;
}
