import QtQuick 2.0

Item {
    id: root
    property alias srcload: loader.source
    Loader {
        id: loader
    }

//    Image {
//        id: demo
//        anchors.centerIn: parent
//        fillMode: "PreserveAspectFit"
//    }


//    Rectangle {
//        id: closeBtn
//        width: 80
//        height: 25
//        border.width: 2
//        border.color: "black"
//        Text {
//            anchors.centerIn: parent
//            text: qsTr("Close")
//        }
//        MouseArea {
//            anchors.fill: parent
//            onClicked: {
//                drawer.state = "";
//            }
//        }
//    }
//    Component.onCompleted: console.log("hehe")
}
