#include <QtWidgets/QApplication>
#include <QtQml>
#include <QtQuick/QQuickView>

#include "utils/PathUtils.h"
#include "utils/QmlRegisterTypes.h"
#include "vk/VKAuth.h"
#include "vk/VkSocialRequestFactory.h"

#include "db/FriendsDb.h"

#include "engine/Engine.h"
#include "engine/DefaultSearchStrategy.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("QuateSoft");
    QCoreApplication::setOrganizationDomain("derail.ru");
    QCoreApplication::setApplicationName("SocialHand");

    QApplication app(argc, argv);

    QmlRegisterTypes::registerAll();

    QQmlEngine qmlEngine;
    QQmlComponent component(&qmlEngine);

    QObject::connect(&qmlEngine, SIGNAL(quit()), QCoreApplication::instance(), SLOT(quit()));

    VKAuth vkAuth;
    VkSocialRequestFactory vkSocialRequestFactory;

    FriendsDb db;

//    UserData data(1111, 2, UserData::UserSide::kMyFriend);
//    data.setCity("33");
//    data.setCountry("44");

//    UserData parent(3, 1, UserData::UserSide::kMyFriend);
//    User user(parent, QList<UserData>() << data);

//    db.storeFriends(user);

//    UserData data1(2222, 2, UserData::UserSide::kTargetFriend);
//    data1.setCity("33");
//    data1.setCountry("44");

//    UserData parent1(55, 1, UserData::UserSide::kTargetFriend);
//    User user1(parent1, QList<UserData>() << data1);

//    db.storeFriends(user1);


//    int parent = 1;
//    QStringList l;
//    for (int i = 0; i < 100; i++) {
//        l.append(QString::number(i));
//    }

//    QTime start = QTime::currentTime();

//    for (int i = 0; i < 10000; i++) {
//        l.clear();
//        for (int j = 0; j < 100; j++) {
//            l.append(QString::number(i) + QString::number(j));
//        }
//        db.storeFriends(l, QString::number(i), i);
//    }

//    QTime end = QTime::currentTime();
//    qDebug() << "DB: " << start.msecsTo(end);

    DefaultSearchStrategy searchStrategy;

    Engine engine(&vkAuth, &vkSocialRequestFactory, &db, &searchStrategy);

    QQmlContext* context = qmlEngine.rootContext();
    context->setContextProperty("vkAuth", &vkAuth);
    context->setContextProperty("engine", &engine);


    component.loadUrl(QUrl::fromLocalFile(PathUtils::resourceFolder() + QStringLiteral("qml/main.qml")));
    if ( !component.isReady() ) {
        qWarning("%s", qPrintable(component.errorString()));
        return -1;
    }
    QObject *topLevel = component.create();
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);
    if ( !window ) {
        qWarning("Error: Your root item has to be a Window.");
        return -1;
    }

    window->show();
    return app.exec();
}
