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
    anchors.horizontalCenter: parent.horizontalCenter // ��������� �� �����������
    anchors.top: parent.top// �������� ������ ������
     anchors.topMargin: 20 // �������� ������ ������

    ListView {
        id: listView
         width: parent.height // ���������� ������ ������
         height: parent.height // ������ ������ ����� ������ ��������
         spacing: UserComponent.height
        //anchors.centerIn: parent // ������������ ������ �� ������ ������������� ��������       
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
        apiHandler.fetchData(); // ����� ������ fetchData ��� ������� ������
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
