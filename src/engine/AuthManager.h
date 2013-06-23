#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

class AuthManager
{
public:
    virtual ~AuthManager() { }

    virtual QString getOriginatorUserId() = 0;
};

#endif // AUTHMANAGER_H
