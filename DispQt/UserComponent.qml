import QtQuick 2.3
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Item {
 property string userid: ""
 property string username: ""
 property string email: ""
 property string comment: ""

 height: 50
 


 Rectangle {
    width: 400
    height: 30
    color: "white"
    

    RowLayout {
            anchors.fill: parent
            spacing: 10 // Установите нужный отступ
      
     Text {
        id: userName2
        text: comment
      }

      Text {
        id: userName
        text: username
      }
      Button {
        text: "Подробнее"
        anchors.right: parent.right
      }
     



      CommentPopup {
            id: compopup
            commentpop: comment
            useridpop: userid
        }

     Button {
    text: "Комментировать"
    anchors.centerIn: parent
    anchors.right: parent.right
    onClicked: {
          compopup.open()

       }
    }



      }



 }
}
