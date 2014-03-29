#include "RequestsQueue.h"

#include <QTimer>
#include <QDebug>

#include "engine/SocialRequest.h"

RequestsQueue::RequestsQueue(RequestsQueue::Listener& listener, SocialRequestFactory& socialRequestFactory, QObject* parent)
    : QObject(parent)
    , listener(listener)
    , socialRequestFactory(socialRequestFactory)
{
    scheduleTimer.setInterval(500);
    scheduleTimer.setSingleShot(true);
    connect(&scheduleTimer, SIGNAL(timeout()), this, SLOT(onScheduleTimer()));
}

void RequestsQueue::startRequests(const RequestsList& requests)
{
    if (!requests.isEmpty()) {
        waitingRequests.append(requests);

        schedule();
    }
}

void RequestsQueue::cancelAll()
{
    scheduleTimer.stop();
    waitingRequests.clear();
    if (hasOutgoingRequest()) {
        outgoingRequest->cancel();
    }
}

void RequestsQueue::startRequest(std::shared_ptr<SocialRequest> request)
{
    outgoingRequest = request;

    connect(request.get(), SIGNAL(socialRequestFinished(SocialRequest*)),
            this, SLOT(onSocialRequestFinished(SocialRequest*)));
    connect(request.get(), SIGNAL(socialRequestFailed(SocialRequest*)),
            this, SLOT(onSocialRequestFailed(SocialRequest*)));

    request->startRequest();
}

void RequestsQueue::schedule()
{
    if (!scheduleTimer.isActive()) {
        if (!waitingRequests.isEmpty()) {
            scheduleTimer.start();
        }
    }
}

bool RequestsQueue::hasOutgoingRequest()
{
    return outgoingRequest != nullptr;
}

void RequestsQueue::onSocialRequestFinished(SocialRequest* request)
{
    Q_ASSERT(request == outgoingRequest.get());

    listener.requestFinished(request);

    outgoingRequest = nullptr;
    schedule();
}

void RequestsQueue::onSocialRequestFailed(SocialRequest* request)
{
    Q_ASSERT(request == outgoingRequest.get());
    waitingRequests.push_front(outgoingRequest);
    schedule();
}

void RequestsQueue::onScheduleTimer()
{
    if (!hasOutgoingRequest()) {
        std::shared_ptr<SocialRequest> nextToSend = waitingRequests.dequeue();
        startRequest(nextToSend);
    } else {
        schedule();
    }
}

