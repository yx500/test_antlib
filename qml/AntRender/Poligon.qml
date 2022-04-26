import QtQuick 2.15
import QtQuick.Layouts 1.15

import Apoligon 1.0

Image {
    id: root

    property int idx: -1
    property SeismicPoligonData trace //: ThePoligonRenderControl.getPoligon(idx)//undefined

    source: trace.imageUrl //"image://seismtrace1/yellow"
    sourceSize.height: root.height
    sourceSize.width: root.width
    fillMode: Image.Pad
    cache: false

//    Rectangle{
//        anchors.fill: parent
//        border.color:"purple"
//        color:"transparent"
//        Text{
//            anchors.centerIn: parent
//            text: "w"+parent.width
//        }
//    }
//    Component.onCompleted: console.log("+Poligon", idx, trace)
//    Component.onDestruction: console.log("~Poligon", idx, trace)
}
