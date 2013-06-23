import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0

import "vk"

ApplicationWindow {
    title: qsTr("Hello World")
    width: 640
    height: 480

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        Button {
            text: qsTr("Login")
            onClicked: {
                vkAuthItemId.show()
            }
        }

        Button {
            text: qsTr("Start")
            onClicked: {
                engine.start()
            }
        }
    }




    VKAuthItem {
        id: vkAuthItemId
        onLoginSuccess: {

        }
    }

}