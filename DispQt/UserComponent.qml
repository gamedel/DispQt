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
            spacing: 10
            
      UserEditPopup {
            id: editpopup
            useridedit: userid
            usernameedit: username
            parent: editButton
            anchors.centerIn: parent
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




      Text { 
      id: userName
      Layout.leftMargin: 10
        text: username      
      }
      
     Item { width:  130 - userName.width}
        
     Button {
    id: commentButton
    text: "Комментировать"
    onClicked: {
          compopup.open()

       }
    }
    Button {
      id: editButton
        text: " ! "
        onClicked: {
          editpopup.open()

        }
      }

        Button {
      id: infoButton
        text: "Подробнее"
        onClicked: {
          infopopup.open()

        }
      }

      


  }



 }
}
