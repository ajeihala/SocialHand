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

VKGetFriends::VKGetFriends(QObject *parent) :
    GetFriendsRequest(parent),
    m_reply(nullptr)
{

}

void VKGetFriends::doStartRequest(QString userId)
{
    if (m_reply == nullptr)
    {
        QNetworkAccessManager* manager = getNetworkAccessManager();
        connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinished(QNetworkReply*)));

        QUrl url(QString("https://api.vk.com/method/friends.get?user_id=%1").arg(userId));
        m_reply = manager->get(QNetworkRequest(url));
    }
}

void VKGetFriends::onFinished(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = reply->readAll();
        QString result(bytes);

        QJsonDocument json = QJsonDocument::fromJson(bytes);

        QJsonObject obj = json.object();
        QJsonValue value = obj.value("response");
        QJsonArray array = value.toArray();

        QVariantList variantList = array.toVariantList();
        QStringList list;

        for (QVariant item : variantList) {
            list.append(item.toString());
        }

        emit friendsRequestFinished(this, getUserId(), list);
    }

    reply->deleteLater();
}

QNetworkAccessManager* VKGetFriends::getNetworkAccessManager()
{
    static QNetworkAccessManager manager;
    return &manager;
}
