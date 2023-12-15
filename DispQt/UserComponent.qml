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
      Layout.leftMargin: 10
        id: userName
        text: username      
      }
      
     
      CommentPopup {
            id: compopup
            commentpop: comment
            useridpop: userid
            usernamepop: username
            parent: commentButton
            anchors.centerIn: parent
        }
        UserInfoPopup {
            id: infopopup
            commentinfo: comment
            useridinfo: userid
            usernameinfo: username
            emailinfo: email
            parent: infoButton
            anchors.centerIn: parent
        }


        Button {
      id: infoButton
        text: "Подробнее"
        anchors.right: parent.right
        onClicked: {
          infopopup.open()

        }
      }

      Button {
      id: editButton
        text: "!"
        anchors.right: parent.right
        onClicked: {
          infopopup.open()

        }
      }

     Button {
    id: commentButton
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
