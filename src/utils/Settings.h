#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

class Settings
{
public:
    static QSettings& getInstance();

private:
    Settings();
};

#endif // SETTINGS_H
