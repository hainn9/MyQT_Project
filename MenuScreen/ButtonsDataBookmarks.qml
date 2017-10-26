import QtQuick 2.0

ListModel {
    ListElement {
        event: "listview"
        iconImage: "qrc:/img/icon/icon_bookmarks_list.png"
        reflectionImage: false
        blink: false
        buttonEnabled: true
    }
    ListElement {
        event: "gridview"
        iconImage: "qrc:/img/icon/icon_bookmarks_thumbs.png"
        blink: false
        buttonEnabled: true
    }
}


