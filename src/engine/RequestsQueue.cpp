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
    waitingRequests.append(usersList);

    schedule();
}

void RequestsQueue::startRequest(const UserData& userData)
{
    GetFriendsRequest* friendsRequest = socialRequestFactory.createGetFriendsRequest();
    connect(friendsRequest, SIGNAL(friendsRequestFinished(GetFriendsRequest*,User)),
            this, SLOT(onGetFriendsRequestFinished(GetFriendsRequest*,User)));
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

void RequestsQueue::onGetFriendsRequestFinished(GetFriendsRequest* request, User user)
{
    request->deleteLater();
    outgoingRequest = nullptr;

    listener.requestFinished(user);
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

