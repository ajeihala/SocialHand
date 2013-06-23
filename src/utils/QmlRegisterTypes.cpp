#include "utils/QmlRegisterTypes.h"

#include <QQmlEngine>
#include <QtQml>
#include <QObject>

#include "vk/VKAuth.h"
#include "engine/Engine.h"


QmlRegisterTypes::QmlRegisterTypes()
{ }

void QmlRegisterTypes::registerAll()
{
#define QML_REGISTER(name) qmlRegisterType<name>("SocialHand", 1, 0, #name);

    QML_REGISTER(VKAuth);
    QML_REGISTER(Engine);

#undef QML_REGISTER
}
