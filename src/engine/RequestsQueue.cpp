#include "RequestsQueue.h"

#include <QTimer>
#include <QDebug>

#include "engine/SocialRequestFactory.h"
#include "engine/GetFriendsRequest.h"

RequestsQueue::RequestsQueue(RequestsQueue::Listener& listener, SocialRequestFactory& socialRequestFactory, QObject* parent)
    : QObject(parent)
    , _listener(listener)
    , _socialRequestFactory(socialRequestFactory)
{
}

void RequestsQueue::startRequests(QStringList userIdList, int level)
{
    for (QString userId : userIdList) {
        _waitingRequests.enqueue(WaitingRequest(userId, level));
    }

    schedule();
}

void RequestsQueue::startRequest(QString userId, int level)
{
    GetFriendsRequest* friendsRequest = _socialRequestFactory.createGetFriendsRequest();
    connect(friendsRequest, SIGNAL(friendsRequestFinished(GetFriendsRequest*,QString,QStringList)),
            this, SLOT(onGetFriendsRequestFinished(GetFriendsRequest*,QString,QStringList)));

    _levelsMap.insert(friendsRequest, level);
    friendsRequest->startRequest(userId);
}

void RequestsQueue::schedule()
{
    if (!_waitingRequests.isEmpty() && !hasOutgoingRequest()) {
        QTimer::singleShot(500, this, SLOT(onScheduleTimer()));
    }
}

bool RequestsQueue::hasOutgoingRequest()
{
    return !_levelsMap.isEmpty();
}

void RequestsQueue::onGetFriendsRequestFinished(GetFriendsRequest* request, QString userId, QStringList friendsList)
{
    qDebug() << "List for user id: " << userId << " : " << friendsList;

    auto iter = _levelsMap.find(request);
    if (iter != _levelsMap.end()) {
        int level = iter.value();
        _listener.requestFinished(userId, friendsList, level);
        _levelsMap.erase(iter);
    }

    request->deleteLater();

    schedule();
}

void RequestsQueue::onScheduleTimer()
{
    WaitingRequest nextToSend = _waitingRequests.dequeue();
    startRequest(nextToSend.userId, nextToSend.level);
}

