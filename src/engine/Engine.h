#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QStringList>

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
    void start(QString target);
    
private: // RequestsQueue::Listener
    virtual void requestFinished(QList<UserData> users);

private:
    void startRequests(QList<UserData> usersList);
    void processSearchIteration(QList<UserData> users);

private:
    AuthManager* authManager;
    SocialRequestFactory* socialRequestFactory;
    FriendsStorage* storage;
    SearchStrategy* searchStrategy;

    int targetUserId;
    RequestsQueue requestsQueue;
};

#endif // ENGINE_H
