#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QStringList>

class AuthManager;
class SocialRequestFactory;
class GetFriendsRequest;
class FriendsStorage;

class Engine : public QObject
{
    Q_OBJECT
public:
    Engine(AuthManager* auth, SocialRequestFactory* socialRequest, FriendsStorage* storage, QObject* parent = 0);

    // for qml only
    explicit Engine(QObject* parent = 0);
signals:
    
public slots:
    void start();
    
private slots:
    void onGetFriendsRequestFinished(GetFriendsRequest* request, QString userId, QStringList friendsList);

private:
    AuthManager* _authManager;
    SocialRequestFactory* _socialRequest;
    FriendsStorage* _storage;
};

#endif // ENGINE_H
