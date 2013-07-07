#include "engine/User.h"

User::User()
    : User(0, 0, 0, UserSide::kMyFriend)
{
}

User::User(int userId, int parentId, int level, UserSide userSide)
    : userId(userId)
    , parentId(parentId)
    , level(level)
    , userSide(userSide)
    , timezone(0)
{
}

int User::getUserId() const
{
    return userId;
}

void User::setUserId(int value)
{
    userId = value;
}

int User::getParentId() const
{
    return parentId;
}

void User::setParentId(int value)
{
    this->parentId = value;
}

int User::getTimezone() const
{
    return timezone;
}

void User::setTimezone(int value)
{
    timezone = value;
}

User::UserSide User::getUserSide() const
{
    return userSide;
}

void User::setUserSide(const User::UserSide& value)
{
    this->userSide = value;
}

QString User::getHomeTown() const
{
    return homeTown;
}

void User::setHomeTown(const QString& value)
{
    homeTown = value;
}

QString User::getCity() const
{
    return city;
}

void User::setCity(const QString& value)
{
    city = value;
}
int User::getLevel() const
{
    return level;
}

void User::setLevel(int value)
{
    level = value;
}

QString User::getCountry() const
{
    return country;
}

void User::setCountry(const QString& value)
{
    this->country = value;
}


QDebug operator <<(QDebug d, const User& userData)
{
    d << "[" << userData.getUserId() << "]";
    return d;
}



