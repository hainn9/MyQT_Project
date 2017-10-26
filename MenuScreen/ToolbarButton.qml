import QtQuick 2.0

Item {
    id: wrapper

    // Current selection state (on/off)
    property bool selected: false

    width: 50
    height:  50
    opacity: buttonEnabled ? 0.5 : 0

    // Button icon
    Image {
        id: icon

        anchors.centerIn: parent
        source: iconImage

        // Blinking animation, which
        // is done if 'blink' property is true
        SequentialAnimation {
            loops: Animation.Infinite
            running: blink

            PropertyAnimation {
                target: icon
                property: "opacity"
                from: 1.0; to: 0.0
                duration: 1000
            }
            PropertyAnimation {
                target: icon
                property: "opacity"
                from: 0.0; to: 1.0
                duration: 1000
            }
        }
    }

    // Selected state displays the icon
    // and button highlighted
    states:
        State {
            name: "selected"
            when: selected

            PropertyChanges {
                target: wrapper
                opacity: 1

            }
        }

    transitions:
        Transition {
            to: "selected"
            reversible: true

            NumberAnimation { properties: "opacity"; duration: 500 }
        }
}

