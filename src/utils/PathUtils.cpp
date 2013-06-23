#include "utils/PathUtils.h"

#include <QDesktopServices>
#include <QtWidgets/QApplication>

QString PathUtils::resourceFolder()
{
    return QApplication::applicationDirPath() + "/../";
}

QString PathUtils::storageFolder()
{
    return QApplication::applicationDirPath() + "/../";
}
