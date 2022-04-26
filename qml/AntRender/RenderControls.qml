import QtQuick 2.15
import Qt.labs.settings 1.0

import Apoligon 1.0

RenderControlsForm {
    id: root

    scaleT.onValueChanged: recalc_trace()
    scaleV.onValueChanged: recalc_trace()
    traceWidth.onValueChanged: recalc_trace()
    firstSample.onValueChanged: recalc_trace()


    function recalc_trace() {
        ThePoligonRenderControl.repaintPoligons()
//        var params = {
//            scaleT: ThePoligonRenderControl.scaleT,
//            scaleV:  ThePoligonRenderControl.scaleV,
//            traceWidth: ThePoligonRenderControl.traceWidth,
//            firstSample: ThePoligonRenderControl.firstSample,
//        }
//        console.log("SeismicControl", JSON.stringify(params))
    }

    Component.onCompleted: {
        ThePoligonRenderControl.scaleT = Qt.binding(function() { return  Math.pow(Math.SQRT2, scaleT.value); })
        ThePoligonRenderControl.scaleV = Qt.binding(function() { return  Math.pow(Math.SQRT2, scaleV.value); })
        ThePoligonRenderControl.traceWidth = Qt.binding(function() { return  traceWidth.value; })
        ThePoligonRenderControl.firstSample = Qt.binding(function() { return  firstSample.value; })
    }



//    Settings {
//        id: settings
//        category: "PoligonRenderControls"
//        property alias scaleT: root.scaleT.value
//        property alias scaleV: root.scaleV.value
//        property alias traceWidth: root.traceWidth.value
//    }
}
