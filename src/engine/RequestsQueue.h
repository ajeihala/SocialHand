#ifndef REQUESTSQUEUE_H
#define REQUESTSQUEUE_H

#include <QObject>
#include <QQueue>
#include <QTimer>

#include "engine/User.h"

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

        virtual void requestFinished(const User& user) = 0;
    };

public:
    explicit RequestsQueue(Listener& listener, SocialRequestFactory& socialRequestFactory, QObject *parent = 0);
    
public:
    void startRequests(QList<UserData> usersList);
    void cancellAll();

private:
    void startRequest(const UserData& userData);

    void schedule();

    bool hasOutgoingRequest();

private slots:
    void onGetFriendsRequestFinished(GetFriendsRequest* request, User user);
    void onGetFriendsRequestFailed(GetFriendsRequest* request, UserData userData);
    void onScheduleTimer();

private:
    Listener& listener;
    SocialRequestFactory& socialRequestFactory;
    QQueue<UserData> waitingRequests;
    GetFriendsRequest* outgoingRequest;

    QTimer scheduleTimer;
};

#endif // REQUESTSQUEUE_H
