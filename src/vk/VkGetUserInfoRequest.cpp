#include "VkGetUserInfoRequest.h"

#include <QStringList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QStringList>
#include <QVariantList>

#include "vk/VkHelper.h"

VkGetUserInfoRequest::VkGetUserInfoRequest(const User& user, QObject *parent) :
    GetUserInfoRequest(user, parent)
{
}

QUrl VkGetUserInfoRequest::getRequestUrl(const QString& userId)
{
    QStringList fieldsList;
    fieldsList << VkFields::kUid
               << VkFields::kFirstName
               << VkFields::kLastName
               << VkFields::kNickName
               << VkFields::kScreenName
               << VkFields::kSex
               << VkFields::kBirthdate
               << VkFields::kCity
               << VkFields::kCountry
               << VkFields::kTimeZone
               << VkFields::kPhoto
               << VkFields::kPhotoMedium
               << VkFields::kPhotoBig
               << VkFields::kHasMobile
               << VkFields::kRate
               << VkFields::kContacts
               << VkFields::kEducation
               << VkFields::kOnline;


    VkUrlBuilder builder("users.get");
    builder.addItem("uids", userId)
            .addItem("fields", fieldsList.join(','))
            .addItem("name_case", "nom");

    return builder.build();
}

void VkGetUserInfoRequest::processReceivedResponse(const QByteArray& response)
{
    QJsonDocument json = QJsonDocument::fromJson(response);

    QJsonObject obj = json.object();
    QJsonValue value = obj.value("response");
    QJsonArray array = value.toArray();

    for (QJsonValue value : array) {
        QJsonObject object = value.toObject();

        bool isDeactivated = object.value("deactivated").type() != QJsonValue::Undefined;

        if (!isDeactivated) {
            QJsonValue userIdValue = object.value("user_id");
            QJsonValue countryValue = object.value(VkFields::kCountry);
            QJsonValue cityValue = object.value(VkFields::kCity);
            QJsonValue homeTown = object.value(VkFields::kHomeTown);
            QJsonValue timeZoneValue = object.value(VkFields::kTimeZone);

            UserInfo info;
            info.uid = object.value(VkFields::kUid).toInt();
            info.firstName = object.value(VkFields::kFirstName).toString();
            info.lastName = object.value(VkFields::kLastName).toString();
            info.sex = object.value(VkFields::kSex).toInt();
            info.nickName = object.value(VkFields::kNickName).toString();
            info.screenName = object.value(VkFields::kScreenName).toString();
            info.birthDate = object.value(VkFields::kBirthdate).toString();
            info.city = object.value(VkFields::kCity).toInt();
            info.country = object.value(VkFields::kCountry).toInt();
            info.timeZone = object.value(VkFields::kTimeZone).toInt();
            info.photo = object.value(VkFields::kPhoto).toString();
            info.photoMedium = object.value(VkFields::kPhotoMedium).toString();
            info.photoBig = object.value(VkFields::kPhotoBig).toString();
            info.hasMobile = object.value(VkFields::kHasMobile).toInt();
            info.online = object.value(VkFields::kOnline).toInt();
            info.university = object.value("university").toInt();
            info.universityName = object.value("university_name").toString();
            info.faculty = object.value("faculty").toInt();
            info.facultyName = object.value("faculty_name").toString();

            setUserInfo(info);
        }
    }
}
