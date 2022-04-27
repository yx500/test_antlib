import Pie 1.0
import QtQuick 2.0

Item {
    width: 800; height: 800

    PieChart {
        id: aPieChart
        anchors.fill: parent
        name: "/ste/sta/holoni.ste"
        color: "red"
    }

    Text {
        anchors {
            bottom: parent.bottom;
            horizontalCenter: parent.horizontalCenter;
            bottomMargin: 20
        }
        text: aPieChart.name
    }
}
