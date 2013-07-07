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

    void startRequest(const UserData& userData)
    {
        this->userData = userData;
        doStartRequest(userData.getUserId());
    }

    void cancel() {
        doCancel();
    }

signals:
    void friendsRequestFinished(GetFriendsRequest* request, User user);
    void friendsRequestFailed(GetFriendsRequest* request, UserData userData);

public:
    UserData& getUserData() {
        return userData;
    }

protected:
    virtual void doStartRequest(int userId) = 0;
    virtual void doCancel() = 0;

private:
    UserData userData;
};

#endif // GETFRIENDSREQUEST_H
