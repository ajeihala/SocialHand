#ifndef GETFRIENDSREQUEST_H
#define GETFRIENDSREQUEST_H

#include <QObject>
#include <QString>
#include <QStringList>

#include "engine/User.h"

class GetFriendsRequest : public QObject
{
    Q_OBJECT
public:
    virtual ~GetFriendsRequest() { }
    GetFriendsRequest(QObject* parent = 0)
        : QObject(parent)
    { }

    void startRequest(const User& userData)
    {
        this->userData = userData;
        doStartRequest(userData.getUserId());
    }

    void cancel() {
        doCancel();
    }

signals:
    void friendsRequestFinished(GetFriendsRequest* request, UserList users);
    void friendsRequestFailed(GetFriendsRequest* request, User userData);

public:
    User& getUserData() {
        return userData;
    }

protected:
    virtual void doStartRequest(int userId) = 0;
    virtual void doCancel() = 0;

private:
    User userData;
};

#endif // GETFRIENDSREQUEST_H
