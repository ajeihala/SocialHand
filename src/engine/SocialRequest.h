#ifndef SOCIALREQUEST_H
#define SOCIALREQUEST_H

#include <QStringList>

class SocialRequest
{
public:
    virtual ~SocialRequest() { }

    virtual QStringList getFriendsList(QString userId) = 0;
};

#endif // SOCIALREQUEST_H
