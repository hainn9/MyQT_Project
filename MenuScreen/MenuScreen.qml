import QtQuick 2.0
import QtQuick.Window 2.0



Item {
    id: mainView
//    width: 650
//    height: 390

    property alias bookmarkMode: bookmarkView.state  // "gridview" or "listview"

    // Handle toolbar and 'openUrl' events
    function handleToolbarEvent(event) {
        switch (event) {
            // When switching grid and list views
            // second press on the same view mode switches
            // between browser and bookmarks
            case "gridview":    // Fall through
            case "listview":
                if (mainView.state == "bookmarks" &&
                    bookmarkMode == event)
                {
                    mainView.state = "browser";
                }
                else {
                    mainView.state = "bookmarks";
                    bookmarkMode = event;
                }
                break;
        }
    }

    function openApp(srcApp) {
        browserView.openApp(srcApp)
    }

    AppView {
        id: browserView
        anchors.fill: parent
        clip: true
    }

    MenuView {
        id: bookmarkView
        anchors.fill: parent
        state: "gridview"
        onBookmarkSelected: {
            browserView.openApp(srcApp)
            browserView.focus = true
            // Start displaying browser view
            mainView.state = "browser"
        }
    }
    states: [
        State {
            name: "bookmarks"
            PropertyChanges{
                target: bookmarkView
                y: 0
                opacity: 1
            }
            PropertyChanges {
                target: browserView
                opacity: 0
                height: 0
            }
            StateChangeScript { script: setToolbarModel(toolbarBtnsBookmarks) }
        },

        State {
            name: "browser"
            PropertyChanges{
                target: bookmarkView
                y: parent.height
                opacity: 0
            }
            PropertyChanges {
                target: browserView
                opacity: 1
                height: mainView.height
            }
            StateChangeScript { script: setToolbarModel(toolbarBtnsBookmarks) }
       }
    ]

    transitions: [
        Transition {
            to: "browser"
            reversible: true
            NumberAnimation { properties: "y,opacity,height"; easing.type: "InOutQuad"; duration: 500 }
        },
        Transition {
            to: "bookmarks"
            reversible: true
            SequentialAnimation {
                NumberAnimation { properties: "y,height"; easing.type: "InOutQuad" ; duration: 500 }
                PauseAnimation { duration: 100 }
                NumberAnimation { properties: "opacity"; easing.type: "OutSine"; duration: 500 }
            }
        }
    ]
}








