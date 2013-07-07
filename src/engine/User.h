#ifndef USER_H
#define USER_H

#include <QString>
#include <QList>

class UserData
{
public:
    UserData();
    UserData(int userId, int level);

public:
    int getUserId() const;
    void setUserId(int value);

    int getLevel() const;
    void setLevel(int value);

    QString getCountry() const;
    void setCountry(const QString& value);

    QString getCity() const;
    void setCity(const QString& value);

    QString getHomeTown() const;
    void setHomeTown(const QString& value);

    int getTimezone() const;
    void setTimezone(int value);

private:
    int userId;
    int level;
    QString country;
    QString city;
    QString homeTown;
    int timezone;
};

class User
{
public:
    static const int kUnknown = - 1;

public:
    User(const UserData& userData, QList<UserData> friends = QList<UserData>());

public:
    UserData getUserData() const;
    void setUserData(const UserData& value);

    QList<UserData> getFriends() const;
    void setFriends(const QList<UserData>& value);

private:
    UserData userData;
    QList<UserData> friends;

};

#endif // USER_H
