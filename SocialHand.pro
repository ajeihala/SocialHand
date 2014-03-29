# Add more folders to ship with the application, here
folder_01.source = resources/qml
folder_01.target = .
DEPLOYMENTFOLDERS = folder_01

QMAKE_CXXFLAGS += -std=c++11

myFiles.sources = resources/qml
myFiles.path = .
DEPLOYMENT += myFiles

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build

QT += widgets qml quick webkitwidgets network sql

INCLUDEPATH += src \

VPATH += \
    src \
    src/libs \

DEPENDPATH += \
    src \
    src/libs
    src/utils

# Installation path
# target.path =

include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    src/utils/PathUtils.h \
    src/vk/VKAuth.h \
    src/utils/QmlRegisterTypes.h \
    src/utils/Settings.h \
    src/vk/VKGetFriends.h \
    src/engine/Engine.h \
    src/engine/AuthManager.h \
    src/engine/GetFriendsRequest.h \
    src/engine/SocialRequestFactory.h \
    src/vk/VkSocialRequestFactory.h \
    src/engine/FriendsStorage.h \
    src/db/FriendsDb.h \
    src/engine/RequestsQueue.h \
    src/engine/User.h \
    src/engine/SearchStrategy.h \
    src/engine/DefaultSearchStrategy.h \
    src/engine/SocialRequest.h

SOURCES += \
    src/main.cpp \
    src/utils/PathUtils.cpp \
    src/vk/VKAuth.cpp \
    src/utils/QmlRegisterTypes.cpp \
    src/utils/Settings.cpp \
    src/vk/VKGetFriends.cpp \
    src/engine/Engine.cpp \
    src/vk/VkSocialRequestFactory.cpp \
    src/db/FriendsDb.cpp \
    src/engine/RequestsQueue.cpp \
    src/engine/User.cpp \
    src/engine/DefaultSearchStrategy.cpp \
    src/engine/SocialRequest.cpp

OTHER_FILES += \
    qml/main.qml \
    resources/qml/vk/VKAuthItem.qml


#RESOURCES += \
#    resources.qrc
