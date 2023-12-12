// main.qml
import QtQuick 2.9
import QtQuick.Controls 2.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "API Viewer"
    
   /*Component {
    id: listItemDelegate
    Item {
        width: listView.width
        height: 50
        Row {
            Text {
                id: nameLabel
                text: modelData.name
                }
            Text {
                id: emailLabel
                text: modelData.email
                anchors.left: nameLabel.right
                anchors.leftMargin: 10
                }
            }
         }
     }*/

  // UserComponent {
        //id: myComponent
       // text: "Hello, world!"
        //anchors.centerIn: parent
  //  }


  ScrollView {
    width: 200
    anchors.horizontalCenter: parent.horizontalCenter // Выровнять по горизонтали
    anchors.top: parent.top// Добавить отступ сверху
     anchors.topMargin: 20 // Добавить отступ сверху

    ListView {
        id: listView
         width: parent.height // Установите ширину списка
         height: parent.height // Высота списка равна высоте родителя
         spacing: UserComponent.height
        //anchors.centerIn: parent // Выравнивание списка по центру родительского элемента       
         delegate: UserComponent {
        text: modelData.name
        
       }
      }
    }



    Component.onCompleted: {
        //apiHandler.fetchData();
    }

    Button {
    id: button
    text: "Fetch Data"
    anchors.centerIn: parent
    onClicked: {
        apiHandler.fetchData(); // Вызов метода fetchData при нажатии кнопки
    }
    }


    Connections {
        target: apiHandler
        onDataFetched: {
            var json = JSON.parse(data);
            listView.model = json;
        }
    }

    
}
