// main.qml
import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3


ApplicationWindow {
   title: "База сотрудников"
    visible: true
    width: 640
    height: 600   
    minimumWidth: width
    maximumWidth: width
    minimumHeight: height
    maximumHeight: height
   

ColumnLayout  {

anchors.horizontalCenter: parent.horizontalCenter
    anchors.top: parent.top

    anchors.topMargin: 20

    RowLayout{
    anchors.horizontalCenter: parent.horizontalCenter
    spacing: 30 
     Text{
     text:"Сотрудники:"  
      font.pixelSize: 20 
     }
      Button {
     id: requestbt
     text: "Получить список"
     onClicked: {
        controller.requestData(); 
       }
      }
     }
     
     Item { height: 20 }

  ScrollView {
    Layout.fillWidth: true
    Layout.preferredHeight: 400
    width:width+200

     clip: true
    anchors.horizontalCenter: parent.horizontalCenter

    ListView {
        id: listView
         height: parent.height
         
         spacing: UserComponent.height    
        
        delegate: UserComponent {
        userid: modelData.id
        username: modelData.name
        email: modelData.email
        comment: modelData.comment     
       }

      }
    }


    }


    Component.onCompleted: {
        controller.refreshUI();
    }


    Connections {
        target: controller
        onDataFetched: {
            var json = JSON.parse(data);
            listView.model = json;
        }
    }

    
}
