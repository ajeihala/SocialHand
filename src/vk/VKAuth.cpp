#include "VKAuth.h"

#include "utils/Settings.h"

QString VKAuth::kVkGroup = "vkontakte";
QString VKAuth::kUserId = "user_id";
QString VKAuth::kAccessToken = "accessToken";
QString VKAuth::kExpiresIn = "expiresIn";

VKAuth::VKAuth(QObject *parent) :
    QObject(parent)
{

}

void VKAuth::saveLoginInformation(QString userId, QString accessToken, QString expiresIn)
{
    QSettings& settings = Settings::getInstance();
    settings.beginGroup(kVkGroup);
    settings.setValue(kUserId, userId);
    settings.setValue(kAccessToken, accessToken);
    settings.setValue(kExpiresIn, expiresIn);
    settings.endGroup();
}

int VKAuth::getOriginatorUserId()
{
    int userId = getSetting(kUserId).toInt();
    return userId;
}

QString VKAuth::getAccessToken()
{
    QString accessToken = getSetting(kAccessToken).toString();
    return accessToken;
}

QVariant VKAuth::getSetting(QString key)
{
    QSettings& settings = Settings::getInstance();
    settings.beginGroup(kVkGroup);
    QVariant result = settings.value(key);
    settings.endGroup();
    return result;
}
