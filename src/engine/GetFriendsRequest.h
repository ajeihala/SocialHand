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

    void startRequest(const User& user)
    {
        this->user = user;
        doStartRequest(user.getUserId());
    }

    void cancel() {
        doCancel();
    }

signals:
    void friendsRequestFinished(GetFriendsRequest* request, UserList users);
    void friendsRequestFailed(GetFriendsRequest* request, User user);

public:
    User& getUser() {
        return user;
    }

protected:
    virtual void doStartRequest(int userId) = 0;
    virtual void doCancel() = 0;

private:
    User user;
};

#endif // GETFRIENDSREQUEST_H
