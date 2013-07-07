#ifndef USER_H
#define USER_H

#include <QString>
#include <QList>
#include <QDebug>

class User
{
public:
    enum class UserSide {
        kMyFriend,
        kTargetFriend
    };

    User();
    User(int userId, int parentId, int level, UserSide userSide);

public:
    int getUserId() const;
    void setUserId(int value);

    int getParentId() const;
    void setParentId(int value);

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

    UserSide getUserSide() const;
    void setUserSide(const UserSide& value);

private:
    int userId;
    int parentId;
    int level;
    UserSide userSide;
    QString country;
    QString city;
    QString homeTown;
    int timezone;
};

typedef QList<User> UserList;

QDebug operator<< (QDebug d, const User& user);

#endif // USER_H
