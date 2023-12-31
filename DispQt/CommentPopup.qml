﻿import QtQuick 2.3
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

ColumnLayout {
            anchors.horizontalCenter: parent.horizontalCenter
            Item { height: 10 }
            Text {
                text: usernamepop
                anchors.horizontalCenter: parent.horizontalCenter
            }
             
             Item { height: 20 }

            Text {
                text: "Комментарий:"
                anchors.horizontalCenter: parent.horizontalCenter
            }
            TextField {
                id: textField
                text: commentpop
                Layout.preferredWidth: 200
                anchors.horizontalCenter: parent.horizontalCenter
                placeholderText: "Введите текст здесь"
            }
            Item { height: 20 }
            Button {
                text: "ОК"
                anchors.horizontalCenter: parent.horizontalCenter
                Layout.preferredWidth: 50

                onClicked: {
                controller.commentData(useridpop, textField.text);
                commentpopup.close()
                    
                }
            }
        }



}