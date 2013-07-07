#include "RequestsQueue.h"

#include <QTimer>
#include <QDebug>

#include "engine/SocialRequestFactory.h"
#include "engine/GetFriendsRequest.h"

RequestsQueue::RequestsQueue(RequestsQueue::Listener& listener, SocialRequestFactory& socialRequestFactory, QObject* parent)
    : QObject(parent)
    , listener(listener)
    , socialRequestFactory(socialRequestFactory)
    , outgoingRequest(nullptr)
{
    scheduleTimer.setInterval(500);
    scheduleTimer.setSingleShot(true);
    connect(&scheduleTimer, SIGNAL(timeout()), this, SLOT(onScheduleTimer()));
}

void RequestsQueue::startRequests(QList<UserData> usersList)
{
    if (!usersList.isEmpty()) {
        waitingRequests.append(usersList);

        schedule();
    }
}

void RequestsQueue::cancellAll()
{
    scheduleTimer.stop();
    waitingRequests.clear();
    if (hasOutgoingRequest()) {
        outgoingRequest->cancel();
    }
}

void RequestsQueue::startRequest(const UserData& userData)
{
    GetFriendsRequest* friendsRequest = socialRequestFactory.createGetFriendsRequest();
    connect(friendsRequest, SIGNAL(friendsRequestFinished(GetFriendsRequest*,QList<UserData>)),
            this, SLOT(onGetFriendsRequestFinished(GetFriendsRequest*,QList<UserData>)));
    connect(friendsRequest, SIGNAL(friendsRequestFailed(GetFriendsRequest*,UserData)),
            this, SLOT(onGetFriendsRequestFailed(GetFriendsRequest*,UserData)));

    outgoingRequest = friendsRequest;
    friendsRequest->startRequest(userData);
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

void RequestsQueue::onGetFriendsRequestFinished(GetFriendsRequest* request, QList<UserData> users)
{
    request->deleteLater();
    outgoingRequest = nullptr;

    listener.requestFinished(users);
    schedule();
}

void RequestsQueue::onGetFriendsRequestFailed(GetFriendsRequest* request, UserData userData)
{
    request->deleteLater();
    outgoingRequest = nullptr;

    waitingRequests.push_front(userData);
    schedule();
}

void RequestsQueue::onScheduleTimer()
{
    if (!hasOutgoingRequest()) {
        UserData nextToSend = waitingRequests.dequeue();
        startRequest(nextToSend);
    } else {
        schedule();
    }
}

