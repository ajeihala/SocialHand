#ifndef VKHELPER_H
#define VKHELPER_H

#include <QString>
#include <QUrlQuery>

class VkFields {
public:
    static const QString kUid;
    static const QString kFirstName;
    static const QString kLastName;
    static const QString kNickName;
    static const QString kScreenName;
    static const QString kSex;
    static const QString kBirthdate;
    static const QString kCity;
    static const QString kCountry;
    static const QString kTimeZone;
    static const QString kPhoto;
    static const QString kPhotoMedium;
    static const QString kPhotoBig;
    static const QString kHasMobile;
    static const QString kRate;
    static const QString kContacts;
    static const QString kEducation;
    static const QString kOnline;
    static const QString kHomeTown;

};

class VkUrlBuilder {
public:
    VkUrlBuilder(QString methodName);

public:
    VkUrlBuilder& addItem(QString key, QString value);
    QUrl build();

private:
    static const QString kMainUrl;

private:
    const QString methodName;
    QUrlQuery urlQuery;

};

#endif // VKHELPER_H
