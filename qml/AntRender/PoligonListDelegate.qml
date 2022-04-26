import QtQuick 2.15
import QtQml.Models 2.1
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

import Apoligon 1.0

MouseArea {
    id: dragArea

    required property int idxProvider
    required property int ffid
    required property string point_addr
//    required property int line
//    required property int point

    property bool held: false

    height: ListView.view ? ListView.view.height : 500;
    width: ThePoligonRenderControl.traceWidth

    drag.axis: Drag.XAxis
    drag.target: held ? content : undefined

    onPressAndHold: held = true
    onReleased: held = false

    Rectangle {
        id: content
        height: dragArea.height;
        width: dragArea.width
//        border.color: "lightsteelblue"

        color: dragArea.held ? "lightsteelblue" : "transparent"
        Behavior on color { ColorAnimation { duration: 80 } }

        Drag.active: dragArea.held
        Drag.source: dragArea
        Drag.hotSpot.x: width / 2
        Drag.hotSpot.y: height / 2

        states: State {
            when: dragArea.held
            ParentChange { target: content; parent: dragArea }
            AnchorChanges {
                target: content
                anchors { horizontalCenter: undefined; verticalCenter: undefined }
            }
        }

        //delegat
        ColumnLayout {
            id: delegat
            height: parent.height
            anchors.centerIn: parent
            Text {
                text: PoligonsBackend.generate_string_key(ffid,point_addr)
                font.pixelSize: Qt.application.font.pixelSize*0.7
                horizontalAlignment: Text.AlignHCenter
                Layout.alignment: Qt.AlignCenter
//                Rectangle{
//                    anchors.fill: parent
//                    color: "transparent"
//                    border.color: "red"
//                }
            }
            Poligon{
                Layout.alignment: Qt.AlignCenter
                Layout.fillHeight: true
                width: content.width
                idx: idxProvider
                trace: ThePoligonRenderControl.get(idxProvider)
            }
        }

    }

    DropArea {
        anchors { fill: parent; margins: 2 }
        onEntered: (drag) => {
                       visualModel.items.move(
                           drag.source.DelegateModel.itemsIndex,
                           dragArea.DelegateModel.itemsIndex)
                   }
    }
}


