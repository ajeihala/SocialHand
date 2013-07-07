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
    explicit VKGetFriends(QObject* parent = 0);
    
public: // GetFriendsRequest
    virtual void doStartRequest(int userId);
    virtual void doCancel();

private slots:
    void onFinished(QNetworkReply* finishedReply);

private:
    static QNetworkAccessManager* getNetworkAccessManager();

    QNetworkReply* reply;
};

#endif // VKGETFRIENDS_H
