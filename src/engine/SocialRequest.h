#ifndef SOCIALREQUEST_H
#define SOCIALREQUEST_H

#include <QObject>
#include <QUrl>
#include <memory>

#include "engine/User.h"

class QNetworkAccessManager;
class QNetworkReply;

class SocialRequest : public QObject
{
    Q_OBJECT
public:
    enum class Type
    {
        kGetUserInfo,
        kGetFriends
    };

public:
    explicit SocialRequest(Type type, const User& user, QObject *parent = 0);
    void startRequest();
    void cancel();

public:
    const User& getUser() {
        return user;
    }

    Type getType() {
        return type;
    }

signals:
    void socialRequestFinished(SocialRequest* request);
    void socialRequestFailed(SocialRequest* request);

protected:
    virtual QUrl getRequestUrl(const QString& userId) = 0;
    virtual void processReceivedResponse(const QByteArray& response) = 0;

private slots:
    void onFinished(QNetworkReply* finishedReply);

private:
    static QNetworkAccessManager* getNetworkAccessManager();

private:
    const Type type;
    QNetworkReply* reply;
    const User user;
};

typedef QList<std::shared_ptr<SocialRequest>> RequestsList;

#endif // SOCIALREQUEST_H
