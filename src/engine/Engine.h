#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>

class AuthManager;
class SocialRequest;

class Engine : public QObject
{
    Q_OBJECT
public:
    Engine(AuthManager* auth, SocialRequest* socialRequest, QObject* parent = 0);

    // for qml only
    explicit Engine(QObject* parent = 0);
signals:
    
public slots:
    void start();
    

private:
    AuthManager* _authManager;
    SocialRequest* _socialRequest;
};

#endif // ENGINE_H
