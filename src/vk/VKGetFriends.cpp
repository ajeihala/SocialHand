#include "VKGetFriends.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

VKGetFriends::VKGetFriends(QString userId, QObject *parent) :
    QObject(parent)
{
    QNetworkAccessManager* manager = getNetworkAccessManager();
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinished(QNetworkReply*)));

    QUrl url(QString("https://api.vk.com/method/friends.get?user_id=%1").arg(userId));
    manager->get(QNetworkRequest(url));
}

void VKGetFriends::onFinished(QNetworkReply* reply)
{
    QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = reply->readAll();
        QString result(bytes);
        qDebug() << result;

        QJsonDocument json = QJsonDocument::fromJson(bytes);
        qDebug() << "array: " << json.isArray();
        qDebug() << "object: " << json.isArray();

        QJsonObject obj = json.object();
        QJsonValue value = obj.value("response");
        QJsonArray array = value.toArray();

        qDebug() << "count: " << array.count();
    }

    reply->deleteLater();
}

QNetworkAccessManager* VKGetFriends::getNetworkAccessManager()
{
    static QNetworkAccessManager manager;
    return &manager;
}


//https://api.vk.com/method/getProfiles?uid=66748&access_token=533bacf01e11f55b536a565b57531ac114461ae8736d6506a3
