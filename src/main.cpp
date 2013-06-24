#include <QtWidgets/QApplication>
#include <QtQml>
#include <QtQuick/QQuickView>

#include "utils/PathUtils.h"
#include "utils/QmlRegisterTypes.h"
#include "vk/VKAuth.h"
#include "vk/VkSocialRequestFactory.h"

#include "db/FriendsDb.h"

#include "engine/Engine.h"

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

    Engine engine(&vkAuth, &vkSocialRequestFactory, &db);

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
