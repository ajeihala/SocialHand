#ifndef REQUESTSQUEUE_H
#define REQUESTSQUEUE_H

#include <QObject>
#include <QMap>
#include <QStringList>
#include <QQueue>

class GetFriendsRequest;
class SocialRequestFactory;

class RequestsQueue : public QObject
{
    Q_OBJECT

public:
    class Listener
    {
    public:
        virtual ~Listener() { }

        virtual void requestFinished(QString parentId, QStringList friendsList, int level) = 0;
    };

public:
    explicit RequestsQueue(Listener& listener, SocialRequestFactory& socialRequestFactory, QObject *parent = 0);
    
public:
    void startRequests(QStringList userIdList, int level);

private:
    void startRequest(QString userId, int level);

    void schedule();

    bool hasOutgoingRequest();

private slots:
    void onGetFriendsRequestFinished(GetFriendsRequest* request, QString userId, QStringList friendsList);
    void onScheduleTimer();

private:
    Listener& _listener;
    SocialRequestFactory& _socialRequestFactory;
    QMap<GetFriendsRequest*, int> _levelsMap;

    class WaitingRequest
    {
    public:
        QString userId;
        int level;
        WaitingRequest(QString userId, int level)
        {
            this->userId = userId;
            this->level = level;
        }
    };

    QQueue<WaitingRequest> _waitingRequests;
};

#endif // REQUESTSQUEUE_H
