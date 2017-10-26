import QtQuick 2.0

Item {
    id: wrapper

    // Zoom value when zooming with double click

    property alias contentWidth: browserView.contentWidth
    property alias contentHeight: browserView.contentHeight
    property alias contentX: browserView.contentX
    property alias contentY: browserView.contentY

    function openApp(srcApp) {
        loader.source = srcApp
    }
    Flickable {
        id: browserView

        anchors.fill: parent
        // Allocate size for content which is at least as big as the view area
        contentWidth: parent.width
        contentHeight: parent.height

        // Black background for the browserView
        Rectangle  {
            id: browserBackground
            anchors.fill: parent
            color: 'black'
            Loader {
                id: loader
            }
        }
    }
}

