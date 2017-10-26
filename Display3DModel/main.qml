import QtQuick 2.0
import SceneGraphRendering 1.0
import QtGraphicalEffects 1.0

Rectangle {
    id: root
    width: 800
    height: 480
    color: "black"

    property real rotValue: 0.0
    property bool inc: true
    Renderer {
        id: renderer
        width: 525
        height: 480
        x: 137.5
        y: 0
        rotX: 0.0
        rotY: rotValue
        rotZ: 0.0
        dX: 0.0
        dY: 0.0
        dZ: 0.0
        scaleValue: 1.0
    }

//    Glow {
//        anchors.fill: renderer
//        radius: 8
//        samples: 17
//        color: "white"
//        spread: 0.5
//        source: renderer
//    }

    Timer {
        id: timer
        interval: 50
        repeat: true
        running: false
        onTriggered: {
            rotValue += 5.0
        }
    }
    MouseArea {
        anchors.fill: parent
        onClicked: timer.running = !timer.running
    }
}

