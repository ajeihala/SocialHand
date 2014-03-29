#ifndef REQUESTSQUEUE_H
#define REQUESTSQUEUE_H

#include <QObject>
#include <QQueue>
#include <QTimer>

#include "engine/User.h"
#include "engine/SocialRequestFactory.h"

class SocialRequest;

class RequestsQueue : public QObject
{
    Q_OBJECT

public:
    class Listener
    {
    public:
        virtual ~Listener() { }

        virtual void requestFinished(SocialRequest* request) = 0;
    };

public:
    explicit RequestsQueue(Listener& listener, SocialRequestFactory& socialRequestFactory, QObject *parent = 0);
    
public:
    void startRequests(const RequestsList& requests);
    void cancelAll();

private:
    void startRequest(std::shared_ptr<SocialRequest> request);

    void schedule();

    bool hasOutgoingRequest();

private slots:
    void onSocialRequestFinished(SocialRequest* request);
    void onSocialRequestFailed(SocialRequest* request);

    void onScheduleTimer();

private:
    Listener& listener;
    SocialRequestFactory& socialRequestFactory;
    QQueue<std::shared_ptr<SocialRequest>> waitingRequests;
    std::shared_ptr<SocialRequest> outgoingRequest;

    QTimer scheduleTimer;
};

#endif // REQUESTSQUEUE_H
