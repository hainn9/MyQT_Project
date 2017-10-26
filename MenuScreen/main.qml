import QtQuick 2.3
import QtQuick.Window 2.2

Window {
    visible: true
    //    width: Screen.desktopAvailableWidth
    //    height: Screen.desktopAvailableHeight
    width: 1150; height: 450
    Item {
        id: vmfdScrn
        width: 1150; height: 400
        Image {
            id: bkgrnd
            anchors.fill: parent
            source: "qrc:/img/background.jpg"
//            opacity: 0.3
        }

        MenuApp {
            id: menuApp
//            anchors.centerIn: parent
        }
    }
    Item {
        width: height
        height: parent.height - vmfdScrn.height
        anchors.top: vmfdScrn.bottom
        anchors.horizontalCenter: vmfdScrn.horizontalCenter
        Image {
            id: btn
            source: "qrc:/img/home.png"
            anchors.fill: parent
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                menuApp.state = (menuApp.state == "current")?"":"current"
                bkgrnd.opacity = (menuApp.state == "current")?0.3:1.0
            }
        }
    }
}

