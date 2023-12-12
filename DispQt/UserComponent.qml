import QtQuick 2.3
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Item {
 property alias text: userName.text
 height: 50

 Rectangle {
    width: 200
    height: 30
    color: "white"
    

    RowLayout {
            anchors.fill: parent
            spacing: 10 // Установите нужный отступ
      Text {
        id: userName
      }
      Button {
        text: "Подробнее"
        anchors.right: parent.right
      }
      Button {
        text: "Комментировать"
        anchors.centerIn: parent
        anchors.right: parent.right
      }
    }

 }
}
