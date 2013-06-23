# Add more folders to ship with the application, here
folder_01.source = qml/SocialHand
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build

INCLUDEPATH += src \
        src/libs/vreen \
        src/libs/vreen/src

VPATH += \
    src \
    src/libs \
    src/libs/vreen

DEPENDPATH += \
    src \
    src/libs
    src/utils

include(src/libs/vreen/vreen.pri)

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    src/utils/PathUtils.h

SOURCES += \
    src/main.cpp \
    src/utils/PathUtils.cpp
