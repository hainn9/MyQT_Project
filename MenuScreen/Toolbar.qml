import QtQuick 2.0

Item {
    id: container

    property int bottomMargin: 4
    // model specifies the set of toolbar buttons (ListModel)
    property alias model: buttons.model

    // Notify that a button has been clicked
    // 'event' parameter specifies the triggered event
    signal btnClicked(string event)

    // Set a button highlighted
    function activateButton(index) {
        buttons.currentItem.selected=false;
        buttons.currentIndex = index;
        buttons.currentItem.selected=true;
    }

    // Border of list button
    Rectangle {
        id: background
        border.width: 2
        color: "black"
        border.color:"white"
        width:  parent.width
        height: parent.height-bottomMargin
        radius: 15
        opacity: 0.5
    }

    // Delegate list button
    Component {
        id: btnDrawer
        ToolbarButton {
            id: tbBtn
            x: (container.width -(buttons.model.count*tbBtn.width + (buttons.model.count-1)*buttons.spacing))/2 + index*(tbBtn.width+buttons.spacing)
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (buttonEnabled) {
                        activateButton(index);
                        container.btnClicked(event);
                    }
                }
            }
            Timer {
                interval: 1000
                repeat: true
                running: true
                onTriggered: {
                    console.log(tbBtn.x)
                }
            }
        }
    }

    // ListView
    ListView {
        id: buttons
        anchors.centerIn: parent
        model: {}
        delegate: btnDrawer
        orientation: "Horizontal"
        width: container.width
        height: container.height
        spacing: 15
        interactive: false
    }
}

