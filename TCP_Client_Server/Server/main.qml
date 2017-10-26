import QtQuick 2.0

Item {
    id: root
    property int speed_value: QtPropertyMap.Speed
    width: 654
    height: 654

    Image {
        id: speed
        anchors.fill: parent
        source: "qrc:/image/speed.png"
    }
    Image {
        id: centerSpeed
        anchors.centerIn: parent
        source: "qrc:/image/center.png"
    }

    Image {
        id: needleSpeed
        x: 116
        y: 305
        source: "qrc:/image/needle.png"
        transform: Rotation {
            id: needleRot
            origin.x: 209
            origin.y: 22
            angle: speed_value
        }
    }
}

