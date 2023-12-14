// main.qml
import QtQuick 2.9
import QtQuick.Controls 2.2

ApplicationWindow {
    visible: true
    width: 640
    height: 640
    title: "API Viewer"
    
   

  ScrollView {
    width: 400
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
        userid: modelData.id
        username: modelData.name
        email: modelData.email
        comment: modelData.comment     
       }
      }
    }



    Component.onCompleted: {
        apiHandler.loadCachedData();
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
