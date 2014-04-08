#ifndef SOCIALREQUEST_H
#define SOCIALREQUEST_H

#include <QObject>
#include <QUrl>
#include <memory>

#include "engine/User.h"
#include "engine/AuthManager.h"

class QNetworkAccessManager;
class QNetworkReply;

class SocialRequest : public QObject
{
    Q_OBJECT
public:
    enum class Type
    {
        kGetUserInfo,
        kGetFriends,
        kGetMutualFriends,
    };

public:
    explicit SocialRequest(Type type, const User& user, QObject *parent = 0);
    void startRequest();
    void cancel();

    void setAuthManager(std::shared_ptr<AuthManager> authManager);

public:
    const User& getUser() const {
        return user;
    }

    int getUserId() const {
        return getUser().getUserId();
    }

    Type getType() const {
        return type;
    }

    AuthManager* getAuthManager() {
        return authManager != nullptr ? authManager.get() : nullptr;
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

    std::shared_ptr<AuthManager> authManager;
};

typedef QList<std::shared_ptr<SocialRequest>> RequestsList;

#endif // SOCIALREQUEST_H
