#ifndef VKAUTH_H
#define VKAUTH_H

#include <QObject>

#include "engine/AuthManager.h"

class VKAuth : public QObject, public AuthManager
{
    Q_OBJECT
public:
    explicit VKAuth(QObject *parent = 0);
    
signals:
    
public slots:
    void saveLoginInformation(QString userId, QString accessToken, QString expiresIn);

public: // AuthManager
    virtual QString getOriginatorUserId();

private:
    static QString kVkGroup;
    static QString kUserId;
    static QString kAccessToken;
    static QString kExpiresIn;
};

#endif // VKAUTH_H
