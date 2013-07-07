#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QStringList>

#include "engine/RequestsQueue.h"

class AuthManager;
class SocialRequestFactory;
class FriendsStorage;

class Engine : public QObject, private RequestsQueue::Listener
{
    Q_OBJECT
public:
    Engine(AuthManager* auth, SocialRequestFactory* socialRequestFactory, FriendsStorage* storage, QObject* parent = 0);

    // for qml only
    explicit Engine(QObject* parent = 0);
signals:
    
public slots:
    void start();
    
private: // RequestsQueue::Listener
    virtual void requestFinished(const User& user);

private:
    void startRequests(QList<UserData> usersList);

private:
    AuthManager* _authManager;
    SocialRequestFactory* _socialRequestFactory;
    FriendsStorage* _storage;

    RequestsQueue _requestsQueue;
};

#endif // ENGINE_H
