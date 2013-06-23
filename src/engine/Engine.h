#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QStringList>

class AuthManager;
class SocialRequestFactory;
class GetFriendsRequest;

class Engine : public QObject
{
    Q_OBJECT
public:
    Engine(AuthManager* auth, SocialRequestFactory* socialRequest, QObject* parent = 0);

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
};

#endif // ENGINE_H
