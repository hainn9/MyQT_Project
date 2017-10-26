import QtQuick 2.0

Rectangle {
    id: root
    width: 1150
    height: 400
    color: "black"
    function getTimeStr(showDate) {
        var time = "00:00";
        var days = ["Sun","Mon","Tue","Wed","Thu","Fri","Sat"];
        var months = ["Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"];
        var datetime = new Date()
        var day = datetime.getDay()
        var month = datetime.getMonth()
        var date = datetime.getDate()
        var hours = datetime.getHours();
        var minutes = datetime.getMinutes();

        minutes = minutes < 10 ? "0" + minutes: minutes;

        if (showDate)
            return  days[day] + " " + months[month] + " " + date + ", " + hours + ":" + minutes;
        else
            return  hours + ":" + minutes;
    }

    Text {
        id: timer
        text: ""
        anchors.centerIn: parent
        color: "red"
        font.bold: true
        font.pixelSize: 50

        Timer {
            interval: 10000
            running: true
            repeat: true
            triggeredOnStart: true
            onTriggered: timer.text = getTimeStr(true)
        }
    }

}
