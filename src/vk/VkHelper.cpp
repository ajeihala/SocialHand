#include "vk/VkHelper.h"

const QString VkUrlBuilder::kMainUrl = "https://api.vk.com/method/";

const QString VkFields::kUid = "uid";
const QString VkFields::kFirstName = "first_name";
const QString VkFields::kLastName = "last_name";
const QString VkFields::kNickName = "nickname";
const QString VkFields::kScreenName = "screen_name";
const QString VkFields::kSex = "sex";
const QString VkFields::kBirthdate = "birthdate";
const QString VkFields::kCity = "city";
const QString VkFields::kCountry = "country";
const QString VkFields::kTimeZone = "timezone";
const QString VkFields::kPhoto = "photo";
const QString VkFields::kPhotoMedium = "photo_medium";
const QString VkFields::kPhotoBig = "photo_big";
const QString VkFields::kHasMobile = "has_mobile";
const QString VkFields::kRate = "rate";
const QString VkFields::kContacts = "contacts";
const QString VkFields::kEducation = "education";
const QString VkFields::kOnline = "online";
const QString VkFields::kHomeTown = "home_town";


VkUrlBuilder::VkUrlBuilder(QString methodName)
    : methodName(methodName){

}

VkUrlBuilder& VkUrlBuilder::addItem(QString key, QString value)
{
    urlQuery.addQueryItem(key, value);
    return *this;
}

QUrl VkUrlBuilder::build()
{
    QUrl url(kMainUrl + methodName);
    url.setQuery(urlQuery.query());
    return url;
}
