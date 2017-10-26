import QtQuick 2.5
import QtQuick.Window 2.2

Window {
    id: inteface
    visible: true
    width: Screen.width// 1100
    height:Screen.height// 1100
    title: qsTr("InterFace")
    property int i: 0
    signal clear()
    signal click_search(string data)
    signal to_click(int data)
    signal input_search(string str);
    signal check_input_interver(string str);
    property variant list_suggest:  listv.getSuggest
    property variant list_result:  listv.getResult
    property string set_input_text:  listv.setTextSearch
    property bool set_visible_list_text:  listv.setVisible_List_Text
    property bool set_clear_input_text:  listv.setClear_Input_Text
    property var textip
    Rectangle{
        id: background
        anchors.fill: parent
        focus: true
        Image {
            id: destop //image background
            anchors.fill: parent
            source: "qrc:/fon-pejzazh-sneg-zima-30779.jpg"
        }

        Text {
            id: suggest  // words : "Suggestion Search" above
            anchors.horizontalCenter: parent.horizontalCenter
            y:50
            text: "Suggestion Search"
            font.pixelSize: 50
            color:  "blue"
        }

        Rectangle{
            id: listresult // result search
            x: 20
            y: 400
            width: Screen.width-100 // 1050
            height: 500
            visible: false

            ListView{ // list result search
                anchors.fill: parent
                delegate: Rectangle{
                    id : result
                    width: Screen.width-100// 1050
                    height: 100
                    visible:  (input.text==="")?false : true
                    Text {
                        id:element_result
                        text: list_result[index]
                        font.pixelSize: 40
                        color: "black"
                        x : 30
                        anchors.verticalCenter : parent.verticalCenter
                    }
                }
                model:list_result.length // length of list result
            }
        }

        Rectangle{
            id:listsuggest //suggest search
            x:20
            y:300
            width: Screen.width-100// 1050
            height: 260
            visible: set_visible_list_text //(input.text==="")?false : true
            ListView{
                anchors.fill: parent
                delegate: Rectangle{ //dinh nghia list
                    id : rect
                    width: Screen.width-100// 1050
                    height: 80
                   // visible: set_visible_list_text // (input.text==="")?false : true
                   // color: "yellow"
                    border.width: 0.5
                    border.color: "grey"

                    Text {
                        id:element_suggest
                        text: list_suggest[index]
                        font.pixelSize: 60
                        color: "black"
                        x:30
                        anchors.verticalCenter : parent.verticalCenter
                    }
                    MouseArea{
                        anchors.fill: rect
                        onClicked:{
                            listresult.visible = true ;
                            //listsuggest.visible = false ;
                            //to_click(list_suggest[index]);
                            to_click(index);
                        }
                        onPressed: rect.opacity = 0.5;
                        onReleased: rect.opacity = 1.0;
                    }
                }
                model:list_suggest.length
            }
        }


        Rectangle{
            id:search
            x: 20
            y: 200
            width:  Screen.width
            height: 93// Screen.desktopAvailableHeight

            TextInput{
                id: input
                x: 20
                width:  Screen.width-133
                height: 93
                wrapMode: Text.Wrap
                font.pixelSize:  70
                color: " black"
                text:(set_clear_input_text==true)?"" :set_input_text
                //displayText:set_input_text
                activeFocusOnPress : true
                focus: true
                onTextChanged:{
                    //listsuggest.visible = true ;
                input_search(input.text) ;
                console.log("text change ******");
                }
            }

            Image {
                id: delet
                x: Screen.width- 190// 900
                anchors.verticalCenter: parent.verticalCenter
                source : "qrc:/150px-Cross2.svg.png"
                visible: (input.text === "")? false:true

                MouseArea{
                    anchors.fill: parent
                    onClicked:
                    {
                        //input.text = "" ;
                        clear();
                    }
                    onPressed: delet.opacity = 0.5;
                    onReleased: delet.opacity = 1.0;
                }

            }
        }

        Image {
            id:search_icon
            anchors.right:  search.right
            y: 200
            source: "qrc:/images.png"
            MouseArea{
                anchors.fill: parent
                onClicked:{
                    //listsuggest.visible = true ;
                    //input.text=set_input_text;
                    click_search(input.text);
                }
                onPressed: search_icon.opacity = 0.5;
                onReleased: search_icon.opacity = 1.0;
            }
        }
    }
    Keys.onPressed: {
        /*search_icon.forceActiveFocus();
        search.forceActiveFocus();
        delet.forceActiveFocus();
        input.forceActiveFocus();
        listresult.forceActiveFocus();
        result.forceActiveFocus();
        element_result.forceActiveFocus();
        listsuggest.forceActiveFocus();
        rect.forceActiveFocus();
        element_suggest.forceActiveFocus();*/
        console.log("hhhhhhhhhhssss") ;
    }

    Timer {
        id:timer1
        interval: 600
        running: false
        repeat: true
        onTriggered:
        {
            console.log("text change") ;
            check_input_interver(input.text);
            //input_search(input.text) ;
        }
    }
}
