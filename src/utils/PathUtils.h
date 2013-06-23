#ifndef PATHUTILS_H
#define PATHUTILS_H

#include <QUrl>
#include <QString>

class PathUtils
{
public:
    static QString resourceFolder();
    static QString storageFolder();
};

#endif // PATHUTILS_H
