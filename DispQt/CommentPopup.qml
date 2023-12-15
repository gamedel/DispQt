import QtQuick 2.3
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Popup {

property string useridpop: ""
property string usernamepop: ""
property string commentpop: ""

         id: commentpopup
            width: 300
            height: 200
            modal: true
            focus: true
            closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

Column {
            anchors.centerIn: parent
            
            Text {
                text: usernamepop
                anchors.horizontalCenter: parent.horizontalCenter
            }
             Text {
                text: commentpop
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Text {
                text: "Комментарий:"
                anchors.horizontalCenter: parent.horizontalCenter
            }
            TextField {
                id: textField
                width: parent.width * 0.8
                anchors.horizontalCenter: parent.horizontalCenter
                placeholderText: "Введите текст здесь"
            }

            Button {
                text: "ОК"
                anchors.horizontalCenter: parent.horizontalCenter

                onClicked: {
                apiHandler.commentData(useridpop, textField.text);
                commentpopup.close()
                    
                }
            }
        }



}