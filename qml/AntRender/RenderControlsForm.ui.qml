import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

//import Design 1.0
//import Data 1.0
Rectangle {
    implicitWidth: 600
    implicitHeight: 200
    color: "lightgrey"
    opacity: 0.8
    radius: 4
    anchors.margins: 16

    property alias scaleT: scaleT
    property alias scaleV: scaleV
    property alias traceWidth: traceWidth
    property alias firstSample: firstSample

    GridLayout {
        anchors.fill: parent
        anchors.margins: 8
        rowSpacing: 5
        columns: 2

        Label {
            text: qsTr("Scale Time")
        }
        CustomSlider {
            id: scaleT
            Layout.fillWidth: true
            value: 0
            from: -10
            to: 10
        }
        Label {
            text: qsTr("Scale Value")
        }
        CustomSlider {
            id: scaleV
            Layout.fillWidth: true
            value: 0
            from: -60
            to: 60
        }
        Label {
            text: qsTr("Poligon Width")
        }
        CustomSlider {
            id: traceWidth
            Layout.fillWidth: true
            value: 120
            from: 5
            to: 300
            stepSize: 1
        }
        Label {
            visible: false
            text: qsTr("First Sample")
        }
        CustomSlider {
            visible: false
            id: firstSample
            Layout.fillWidth: true
            value: 0
            from: 0
            to: 20000
            stepSize: 5
        }
    }
}
