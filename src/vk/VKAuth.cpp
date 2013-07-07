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
    QSettings& settings = Settings::getInstance();
    settings.beginGroup(kVkGroup);
    int userId = settings.value(kUserId).toInt();
    settings.endGroup();
    return userId;
}
