import QtQuick 2.0

ListModel {
    ListElement {
        name: "Music"
        appSource: "qrc:/app/MusicApp.qml"
        topNavImage: "music"
    }
    ListElement {
        name: "Navigation"
        appSource: "qrc:/app/NavigationApp.qml"
        topNavImage: "navigation"
    }
    ListElement {
        name: "Weather"
        appSource: "qrc:/app/WeatherApp.qml"
        topNavImage: "weather"
    }
    ListElement {
        name: "Phone"
        appSource: "qrc:/app/PhoneApp.qml"
        topNavImage: "phone"
    }
    ListElement {
        name: "Browser"
        appSource: "qrc:/app/BrowserApp.qml"
        topNavImage: "web"
    }
}
