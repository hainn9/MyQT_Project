import QtQuick 2.3
import QtQuick.Controls 1.0
import SVG 1.0

Rectangle {
    width: 800
    height: 600

    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    SvgImage {
        id: image
        width: 100
        height: 100
        color: "#1156AB"
        scale: "3"
//        source: ":/hazard_warning.svg"
//        newSrc: ":/test.svg"
    }
}

