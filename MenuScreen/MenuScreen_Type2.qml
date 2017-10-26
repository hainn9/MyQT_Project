import QtQuick 2.0
import QtQuick.Window 2.0
import "app"
Flipable {
    id: container
    width: 1150
    height: 400
    property bool flipped: false
    front: //menu list app
           Item {
        id: menuScrn
        anchors.fill: parent
        Item {
            id: menuView
            anchors.centerIn: parent
            clip: true
            width: Screen.desktopAvailableWidth/2.4
            height: Screen.desktopAvailableHeight/7
            MyModel {
                id: model
            }

            Component {
                id: itemDrawer
                Item {
                    width: height
                    height: Screen.desktopAvailableHeight/7
                    Image {
                        id: background
                        anchors.fill: parent
                        source: backgroundImage
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {

                                //TODO: load app not use loader
                                loader.source = appSource;
                                container.flipped = true
                            }
                        }
                    }

                    Image {
                        id: icon
                        source: iconSource
                        scale: 1.5
                        anchors.centerIn: background
                    }
                    Text {
                        id: descriptionField
                        anchors.horizontalCenter: background.horizontalCenter
                        anchors.bottom: background.bottom
                        anchors.bottomMargin: 10
                        text: descriptionText
                        font.pixelSize: 13
                        font.bold: true
                    }
                }
            }
            ListView {
                id: widgetList
                //        width: parent.width
                //        height: parent.height
                anchors.fill: parent
                model: model
                delegate: itemDrawer
                spacing: 10
                orientation: ListView.Horizontal
                focus: true
                interactive: false
            }
        }
    }

    back: //app screen
          Item {
        id: appScrn
        anchors.fill: parent
        Loader {
            id: loader
        }
//        Connections {
//            target: loader.item
//        }
    }

    states: [
        State {
            name: "Flip"
            PropertyChanges { target: rotation; angle: 180 }
            when: container.flipped
        },
        State {
            name: "General"
            PropertyChanges {
                target: object

            }
        },
        State {
            name: "Detail"
            PropertyChanges {
                target: object

            }
        }
    ]

    transitions:
        Transition {
            NumberAnimation { easing.type: "InOutQuad";  property: "angle"; duration: 500 }
        }

    transform:
        Rotation {
            id: rotation
            origin.x: parent.width /2
            origin.y: parent.height/2
            axis.y: 1
            axis.z: 0
        }
}
