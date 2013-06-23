#ifndef GETFRIENDSREQUEST_H
#define GETFRIENDSREQUEST_H

#include <QObject>
#include <QString>
#include <QStringList>

class GetFriendsRequest : public QObject
{
    Q_OBJECT
public:
    virtual ~GetFriendsRequest() { }
    GetFriendsRequest(QObject *parent = 0)
        : QObject(parent)
    { }

    void startRequest(QString userId)
    {
        _userId = userId;
        doStartRequest(userId);
    }

signals:
    void friendsRequestFinished(GetFriendsRequest* request, QString userId, QStringList friendsList);

public:
    QString getUserId() {
        return _userId;
    }

protected:
    virtual void doStartRequest(QString userId) = 0;

private:
    QString _userId;
};

#endif // GETFRIENDSREQUEST_H
