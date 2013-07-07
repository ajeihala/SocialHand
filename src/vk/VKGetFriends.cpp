#include "VKGetFriends.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QStringList>
#include <QVariantList>

#include "engine/User.h"

VKGetFriends::VKGetFriends(QObject *parent) :
    GetFriendsRequest(parent),
    reply(nullptr)
{

}

void VKGetFriends::doStartRequest(int userId)
{
    if (reply == nullptr)
    {
        qDebug() << "Starting request for userId: " << userId;

        QNetworkAccessManager* manager = getNetworkAccessManager();
        connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinished(QNetworkReply*)));

        QUrl url(QString("https://api.vk.com/method/friends.get?user_id=%1&fields=country,city,home_town,timezone").arg(userId));
        reply = manager->get(QNetworkRequest(url));
    }
}

void VKGetFriends::doCancel()
{
    if (reply != nullptr) {
        reply->abort();
    }
}

void VKGetFriends::onFinished(QNetworkReply* finishedReply)
{
    QByteArray bytes = finishedReply->readAll();
    QString result(bytes);

    qDebug() << "VK response for userId " << getUser().getUserId() << ": " << result;

    if (finishedReply->error() == QNetworkReply::NoError && !result.isEmpty())
    {
        QJsonDocument json = QJsonDocument::fromJson(bytes);

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

        emit friendsRequestFinished(this, friendsList);
    } else {
        qDebug() << "Some error on VK request for userId " << getUser().getUserId();
        emit friendsRequestFailed(this, getUser());
    }

    finishedReply->deleteLater();
    reply = NULL;
}

QNetworkAccessManager* VKGetFriends::getNetworkAccessManager()
{
    static QNetworkAccessManager manager;
    return &manager;
}
