#include "SocialRequest.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>


SocialRequest::SocialRequest(Type type, const User& user, QObject *parent)
    : QObject(parent)
    , type(type)
    , reply(nullptr)
    , user(user)
{
}

void SocialRequest::startRequest()
{
    if (reply == nullptr)
    {
        QString userId = QString::number(user.getUserId());
        qDebug() << "Starting request for userId: " << userId;

        QNetworkAccessManager* manager = getNetworkAccessManager();
        connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinished(QNetworkReply*)));

        QUrl url = getRequestUrl(userId);
        reply = manager->get(QNetworkRequest(url));
    }
}

void SocialRequest::cancel()
{
    if (reply != nullptr) {
        reply->abort();
    }
}

void SocialRequest::onFinished(QNetworkReply* finishedReply)
{
    QByteArray bytes = finishedReply->readAll();
    QString result(bytes);

    qDebug() << "Response for userId " << getUser().getUserId() << ": " << result;

    if (finishedReply->error() == QNetworkReply::NoError && !result.isEmpty())
    {
        processReceivedResponse(bytes);
        emit socialRequestFinished(this);
    } else {
        qDebug() << "Some error on request for userId " << getUser().getUserId();
        emit socialRequestFailed(this);
    }

    finishedReply->deleteLater();
    reply = nullptr;
}

QNetworkAccessManager* SocialRequest::getNetworkAccessManager()
{
    static QNetworkAccessManager manager;
    return &manager;
}
