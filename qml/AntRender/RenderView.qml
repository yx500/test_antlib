import QtQuick 2.15

Item {
    id: root
    implicitWidth: 600
    implicitHeight: 1000

    PoligonListView{
        id: listView
        anchors.fill: parent
    }
    RenderControls{
        id: control
        anchors { bottom: listView.bottom; right: listView.right }
    }
}
