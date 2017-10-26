import QtQuick 2.3
import QtQuick.Window 2.2

Window {
    visible: true
    width: 200
    height: 80
    property var src: srcWea
    property int highTemp: Math.round((high-32)*5/9)
    property int lowTemp: Math.round((low-32)*5/9)

    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    Rectangle {
        id: weatherInfo
        width: 200
        height: 80
        border.width: 1
        border.color: "black"
        Text {
            id: text
            y: image.height + 10
            text: lowTemp + "-" + highTemp + "°C"
        }
        Image {
            id: image
            source: {
                var a = src.indexOf("src");
                var b = src.indexOf("gif");
                return src.substring(a+5,b+3);
            }
        }
    }
}

