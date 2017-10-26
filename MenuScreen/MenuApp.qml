import QtQuick 2.0

Item {
    id: app
    width: 1150
    height: 400
    x: width
    state: ""
    function setToolbarModel(model) {
        toolbar.model = model
    }

    function refresh() {
        toolbar.visible = true
    }

    ButtonsDataBookmarks { id: toolbarBtnsBookmarks }
    MenuScreen {
        id: mainView
        state: "bookmarks"
        anchors.fill: parent
    }

    Toolbar {
        id: toolbar
        width: 120
        height: 70
        anchors.left: app.left
        anchors.bottom: app.bottom
        anchors.leftMargin: 10
    }

    states:
        State {
            name: "current"
            StateChangeScript { script: refresh() }
            PropertyChanges { target:app; x: 0 }
            StateChangeScript {
                script: {
                        setToolbarModel(toolbarBtnsBookmarks);
                }
            }
        }

    transitions: [
        Transition {
            to: "current"
            NumberAnimation { properties: "x";easing.type: "InOutQuad"; duration: 500 }
        },
        Transition {
            from: "current"
            NumberAnimation { properties: "x";easing.type: "InOutQuad"; duration: 500 }
        }
    ]

    Connections {
        target: toolbar
        onBtnClicked: mainView.handleToolbarEvent(event)
    }
}

