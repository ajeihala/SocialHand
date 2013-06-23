#include "Settings.h"

#include "utils/PathUtils.h"

QSettings& Settings::getInstance()
{
    static const QString path = PathUtils::storageFolder() + "/Settings.ini";
    static QSettings settings(path, QSettings::IniFormat);
    return settings;
}

Settings::Settings()
{
}
