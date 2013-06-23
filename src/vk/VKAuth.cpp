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

QString VKAuth::getOriginatorUserId()
{
    QSettings& settings = Settings::getInstance();
    settings.beginGroup(kVkGroup);
    QString userId = settings.value(kUserId).toString();
    settings.endGroup();
    return userId;
}
