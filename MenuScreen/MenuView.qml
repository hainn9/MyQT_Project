import QtQuick 2.0
Item {
    id: container
    //    width: 650
    //    height: 390

    // In grid view the bookmarks are
    // allocated in three columns
    property int columns: 3
    // Dimensions for a bookmark in the list view
    property int bmWidth: 0.31*container.width
    property int bmHeight: 110
    property int bmSpacing: 20
    // Bookmark item dimensions
    property real itemHeight: container.height/3
    property real itemWidth: container.width/4
    // Bookmark icon dimensions in the grid view
    property int iconWidth: 0.7*itemWidth
    property int iconHeight: 0.7*itemHeight
    property real xstep: itemWidth + bmSpacing
    // Parameters handing the transition between
    // grid and list views
    property real ystep: 0
    property real ystep3: itemHeight+bmSpacing

    // Signals observers that a bookmark has been selected
    signal bookmarkSelected(string srcApp)

    state: "gridview"
    MyModel {
        id: modelData
    }

    // Bookmark drawer for bookmark list items. The
    // drawer dimensions and position change according
    // to the used bookmark view state (grid or list).
    // In effect, the bookmark list items are transitioned
    // between grid and list layouts
    Component {
        id: bookmarkDrawer

        Item {
            id: wrapper

            width: itemWidth
            height: itemHeight
            // Define the position according to the current
            // animation parameter state
            x: xstep/3 + (index % columns) * xstep
            y: Math.floor(index / columns) * ystep3  + (index % columns)*ystep

            // Border image for the item.
            BorderImage {
                id: bookmarkBackgroundborder
                border.left: 22
                border.top: 20
                border.right: 22
                border.bottom: 20
                horizontalTileMode: BorderImage.Stretch
                verticalTileMode:  BorderImage.Stretch
                width:parent.width
                height: parent.height
                source: (container.state == "gridview")? backgroundImage:"qrc:/img/bar/listbar_internet.png"
            }

            // Bookmark icon obtained from dummydata
            Image {
                id: bookmarkIcon
                y: 5
                anchors.horizontalCenter: parent.horizontalCenter
                source:  iconSource
                width: iconWidth
                height: iconHeight
                fillMode: "PreserveAspectFit"
            }

            // Bookmark title
            Text {
                id: bookmarkText
                font.pixelSize: 18
                font.bold: true
                color: "lightgrey"
                text: descriptionText
                anchors.horizontalCenter: wrapper.horizontalCenter
                // Align the text either below the icon, or middle of the list item
                y: {
                    if (bookmarkIcon.height > (wrapper.height - height) / 2)
                        return anchors.topMargin + bookmarkIcon.y + bookmarkIcon.height
                    else
                        return (wrapper.height - height) / 2
                }
            }

            // When clicking the bookmark item, notify observers
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    container.bookmarkSelected(appSource)
                }
            }
        }
    }
    // The bookmark list. Use Flickable here instead or
    // ListView or GridView to allow switching between
    // list and grid modes in the same component
    Flickable {
        id: flickable
        width: container.width
        height: container.height
        contentWidth: container.width
        contentHeight: repe.height
        clip: true

        // Use Repeater and its delegate property
        // to draw the items in correct positions
        Repeater {
            id: repe
            anchors.fill:parent
            // bookmarkData is obtained from dummydata
            model: modelData
            delegate: bookmarkDrawer
        }
    }

    // The bookmark list has grid and list modes,
    // which are implemented in two states
    states:
        State {
        name: "listview"
        PropertyChanges {
            target: container
            itemHeight: 65
            itemWidth: columns*bmWidth + (columns-1)*bmSpacing
            iconHeight: 0
            iconWidth: 0
            xstep: 0
            ystep: itemHeight + bmSpacing
            ystep3: (itemHeight + bmSpacing) * 3
//            backgroundBorder: "qrc:/img/bar/listbar_internet.png"
        }
    }

    transitions:
        Transition {
        from: "gridview"
        to: "listview"
        reversible: true

        // Carry out the animation in sequence; first
        // the vertical transitions and then horizontal
        // transitions
        SequentialAnimation {
            NumberAnimation {
                properties: "iconHeight,itemHeight,y,ystep,ystep3"
                easing.type: "InOutQuad"
                duration: 1000
            }
            NumberAnimation {
                properties: "iconWidth,itemWidth,x,xstep"
                easing.type: "InOutQuad"
                duration: 1000
            }
        }
    }
}
