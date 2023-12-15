import QtQuick 2.3
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Popup {

property string useridedit: ""
property string usernameedit: ""

         id: editpopup
            width: 300
            height: 150
            modal: true
            focus: true
            closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

ColumnLayout {
            anchors.horizontalCenter: parent.horizontalCenter
            Item { height: 10 }

            Text {
                text: "Задать имя:"
                anchors.horizontalCenter: parent.horizontalCenter
            }
            TextField {
                id: textField
                text: usernameedit
                Layout.preferredWidth: 200
                anchors.horizontalCenter: parent.horizontalCenter
                placeholderText: "Введите имя"
            }
            Item { height: 20 }
            Button {
                text: "ОК"
                anchors.horizontalCenter: parent.horizontalCenter
                Layout.preferredWidth: 50

                onClicked: {
                controller.editUserName(useridedit, textField.text);
                editpopup.close()
                    
                }
            }
        }



}