#ifndef USERINFO_H
#define USERINFO_H

#include <QString>

class UserInfo
{
public:
    UserInfo();

public:
    int uid;
    QString firstName;
    QString lastName;
    int sex;
    QString nickName;
    QString screenName;
    QString birthDate;
    int city;
    int country;
    int timeZone;
    QString photo;
    QString photoMedium;
    QString photoBig;
    int hasMobile;
    int online;
    int university;
    QString universityName;
    int faculty;
    QString facultyName;


};

#endif // USERINFO_H
