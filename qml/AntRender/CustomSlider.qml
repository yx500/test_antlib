import QtQuick 2.15
import QtQuick.Controls 2.15

Slider {
    id: slider
    wheelEnabled: true
    Text{
        anchors {
            right: parent.right//horizontalCenter;
            verticalCenter: parent.verticalCenter
        }
        text:  value.toFixed(2)
    }
}
