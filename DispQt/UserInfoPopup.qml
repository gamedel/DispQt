import QtQuick 2.3
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Popup {

property string useridinfo: ""
property string usernameinfo: ""
property string commentinfo: ""
property string emailinfo: ""

         id: infopopup
            width: 300
            height: 200
            modal: true
            focus: true
            closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

ColumnLayout {
            anchors.horizontalCenter: parent.horizontalCenter
            Item { height: 10 }
            Text {
                text: "Имя: "+usernameinfo
                anchors.horizontalCenter: parent.horizontalCenter
            }
             
             Item { height: 20 }
             Text {
                text: "Почта: "+emailinfo
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Item { height: 20 }
           Text {
                text: "Комментарий: "+commentinfo
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Item { height: 20 }
            Button {
                text: "Закрыть"
                anchors.horizontalCenter: parent.horizontalCenter
                Layout.preferredWidth: 100

                onClicked: {
                infopopup.close()
                    
                }
            }
        }



}