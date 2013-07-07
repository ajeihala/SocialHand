#include "engine/User.h"

UserData::UserData()
    : UserData(0, 0, 0, UserSide::kMyFriend)
{
}

UserData::UserData(int userId, int parentId, int level, UserSide userSide)
    : userId(userId)
    , parentId(parentId)
    , level(level)
    , userSide(userSide)
    , timezone(0)
{
}

int UserData::getUserId() const
{
    return userId;
}

void UserData::setUserId(int value)
{
    userId = value;
}

int UserData::getParentId() const
{
    return parentId;
}

void UserData::setParentId(int value)
{
    this->parentId = value;
}

int UserData::getTimezone() const
{
    return timezone;
}

void UserData::setTimezone(int value)
{
    timezone = value;
}

UserData::UserSide UserData::getUserSide() const
{
    return userSide;
}

void UserData::setUserSide(const UserData::UserSide& value)
{
    this->userSide = value;
}

QString UserData::getHomeTown() const
{
    return homeTown;
}

void UserData::setHomeTown(const QString& value)
{
    homeTown = value;
}

QString UserData::getCity() const
{
    return city;
}

void UserData::setCity(const QString& value)
{
    city = value;
}
int UserData::getLevel() const
{
    return level;
}

void UserData::setLevel(int value)
{
    level = value;
}

QString UserData::getCountry() const
{
    return country;
}

void UserData::setCountry(const QString& value)
{
    this->country = value;
}


User::User(const UserData& userData, QList<UserData> friends)
    : userData(userData)
    , friends(friends)
{
}

UserData User::getUserData() const
{
    return userData;
}

void User::setUserData(const UserData& value)
{
    userData = value;
}

QList<UserData> User::getFriends() const
{
    return friends;
}

void User::setFriends(const QList<UserData>& value)
{
    this->friends = value;
}

QDebug operator <<(QDebug d, const UserData& userData)
{
    d << "[" << userData.getUserId() << "]";
    return d;
}



