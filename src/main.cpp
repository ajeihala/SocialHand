#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"

#include "utils/PathUtils.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QtQuick2ApplicationViewer viewer;

    viewer.setMainQmlFile(PathUtils::resourceFolder() + QStringLiteral("qml/SocialHand/main.qml"));
    viewer.showExpanded();


    return app.exec();
}
