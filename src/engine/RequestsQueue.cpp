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

void RequestsQueue::startRequests(UserList usersList)
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

void RequestsQueue::startRequest(const User& userData)
{
    GetFriendsRequest* friendsRequest = socialRequestFactory.createGetFriendsRequest();
    connect(friendsRequest, SIGNAL(friendsRequestFinished(GetFriendsRequest*,UserList)),
            this, SLOT(onGetFriendsRequestFinished(GetFriendsRequest*,UserList)));
    connect(friendsRequest, SIGNAL(friendsRequestFailed(GetFriendsRequest*,User)),
            this, SLOT(onGetFriendsRequestFailed(GetFriendsRequest*,User)));

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

void RequestsQueue::onGetFriendsRequestFinished(GetFriendsRequest* request, UserList users)
{
    request->deleteLater();
    outgoingRequest = nullptr;

    listener.requestFinished(users);
    schedule();
}

void RequestsQueue::onGetFriendsRequestFailed(GetFriendsRequest* request, User userData)
{
    request->deleteLater();
    outgoingRequest = nullptr;

    waitingRequests.push_front(userData);
    schedule();
}

void RequestsQueue::onScheduleTimer()
{
    if (!hasOutgoingRequest()) {
        User nextToSend = waitingRequests.dequeue();
        startRequest(nextToSend);
    } else {
        schedule();
    }
}

