#ifndef VKGETFRIENDS_H
#define VKGETFRIENDS_H

#include <QObject>
#include "engine/GetFriendsRequest.h"

class QNetworkAccessManager;
class QNetworkReply;

class VKGetFriends : public GetFriendsRequest
{
    Q_OBJECT
public:
    explicit VKGetFriends(QObject *parent = 0);
    
public: // GetFriendsRequest
    virtual void doStartRequest(QString userId);

signals:
    
public slots:
    
private slots:
    void onFinished(QNetworkReply* reply);

private:
    static QNetworkAccessManager* getNetworkAccessManager();

    QNetworkReply* m_reply;
};

#endif // VKGETFRIENDS_H
