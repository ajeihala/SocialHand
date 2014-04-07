#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QStringList>
#include <memory>

#include "engine/RequestsQueue.h"

class AuthManager;
class SocialRequestFactory;
class FriendsStorage;
class SearchStrategy;

class Engine : public QObject, private RequestsQueue::Listener
{
    Q_OBJECT
public:
    Engine(AuthManager* auth, SocialRequestFactory* socialRequestFactory, FriendsStorage* storage, SearchStrategy* searchStrategy, QObject* parent = 0);

    // for qml only
    explicit Engine(QObject* parent = 0);
signals:
    
public slots:
    void start(QString targetUserId);
    
private: // RequestsQueue::Listener
    virtual void requestFinished(SocialRequest* request);

private:
    void processSearchIteration(UserList users);
    QList<std::shared_ptr<SocialRequest>> prepareGetFriendsRequests(const UserList& list);
    void handleFinishedRequest(SocialRequest* request);

private:
    AuthManager* authManager;
    SocialRequestFactory* socialRequestFactory;
    FriendsStorage* storage;
    SearchStrategy* searchStrategy;

    int targetUserId;
    RequestsQueue requestsQueue;
};

#endif // ENGINE_H
