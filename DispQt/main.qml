// main.qml
import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3


ApplicationWindow {
    visible: true
    width: 640
    height: 640
    title: "База сотрудников"
    
   
    



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
        apiHandler.fetchData(); 
       }
      }
     }
     
    

     Item { height: 20 }

  ScrollView {
   // height: 100
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
        apiHandler.loadCachedData();
    }

   


    Connections {
        target: apiHandler
        onDataFetched: {
            var json = JSON.parse(data);
            listView.model = json;
        }
    }


    







    
}
