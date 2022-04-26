import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQml.Models 2.1

import Apoligon 1.0

Rectangle {
    id: root
    implicitWidth: 1280;
    implicitHeight: 1024
//    color: "lightgrey"

    ListView {
        id: view
        anchors { fill: parent; margins: 4 }
        orientation: ListView.Horizontal
        clip: true
        layer.enabled: true  //caching

        model: PoligonsBackend.visualModel

        ScrollBar.horizontal: ScrollBar {
            policy: ScrollBar.AlwaysOn
            stepSize: ThePoligonRenderControl.traceWidth
        }
        ScrollBar.vertical: ScrollBar {
            id: vbar
            policy: ScrollBar.AlwaysOn
            //            hoverEnabled: true
            //            active: hovered || pressed
            //            onPositionChanged: console.log(position)
            size: stepSize / PoligonsBackend.maxSamplesSize * ThePoligonRenderControl.scaleT
            stepSize: (view.height-100)
            onPositionChanged: {
                //todo проверить прорисовку при скаллинге по времени....
                ThePoligonRenderControl.firstSample = position * PoligonsBackend.maxSamplesSize //* ThePoligonRenderControl.scaleT
                ThePoligonRenderControl.repaintPoligons();
//                console.log(position, stepSize, position*PoligonsBackend.maxSamplesSize * ThePoligonRenderControl.scaleT)
            }
        }
        Component.onCompleted: {
            PoligonsBackend.cleanPoligons();
//            PoligonsBackend.add_test_trace(); //todo remove
        }
    }
}

