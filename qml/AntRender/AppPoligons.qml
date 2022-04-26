import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Qt.labs.settings 1.0

import Apoligon 1.0

ApplicationWindow {
    id: window
    title: qsTr("Poligons Render")

    width: 1280
    height: 1024
    visible: true

    RenderView {
        id: seismView
        //        anchors.centerIn: parent
        anchors.fill: parent
    }


    Column{
        anchors {
            top: parent.top
            //            left: parent.horizontalCenter
            right: parent.right
            margins: 30
        }
        Button{
            text: "+push samples from file"
            onClicked: fileDialog.open();
        }
        Button{
            text: "+add empty trace"
            onClicked: PoligonsBackend.pushEmptyPoligon(1000, "#100@22");
        }
        Button{
            text: "+add sin trace"
            onClicked: add(true);
        }
        Button{
            text: "+add random trace"
            onClicked: add(false);
        }
        Button{
            text: "clean"
            onClicked:  PoligonsBackend.cleanPoligons()
        }
    }


    property int _ffid: 100
    function add(sin){
        let a=[]
        var h = 150;
        var samplesCount = 16000
        for(var i=0; i<samplesCount; i++)
            a.push( sin ? (Math.sin(Math.PI/80*i)*h/2) : (Math.random()*h-h/2) )
        PoligonsBackend.addPoligon(a, ++_ffid, sin ? "sin" : "random");
    }


    CustomFileDialog {
        id: fileDialog
        onAccepted: {
            var url =fileDialog.fileUrl
            if(url){
                fileIO.source = url;
                add_from_json( fileIO.readAll() );
            }
        }
    }
    FileIO { id : fileIO }
    function add_from_json(txt){
        var obj = JSON.parse(txt)
        PoligonsBackend.pushPoligon(obj.samples, obj.ffid, obj.uid);
    }


    Settings {
        id: settings
        property alias x: window.x
        property alias y: window.y
        property alias width: window.width
        property alias height: window.height
    }
}
