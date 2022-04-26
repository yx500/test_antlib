pragma Singleton
import QtQuick 2.15
import QtQml.Models 2.2

import Apoligon 1.0

Item {
    id: root

    property DelegateModel visualModel: DelegateModel {
        model: ListModel {
            id: tracesModel
            ListElement {
                idxProvider: -1
                ffid: 999
                point_addr: "#00@00"
            }
        }
        delegate: PoligonListDelegate{}
    }


    property int maxSamplesSize: 0

    function cleanPoligons(){
        tracesModel.clear();
        maxSamplesSize=0;
        for(let i=0; i<ThePoligonRenderControl.size(); ++i)
            ThePoligonRenderControl.get(i).busy=false;
    }

    function delProvider(idx){
        ThePoligonRenderControl.get(idx).busy=false;
    }

    function newProvider(){
        for(let i=0; i<ThePoligonRenderControl.size(); ++i){
            let slot = ThePoligonRenderControl.get(i)
            if( !slot.busy){
                slot.busy=true;
                return slot;
            }
        }
        return ThePoligonRenderControl.get(-1);
    }

    function generate_string_key(ffid, point_addr){
        return ""+ffid+"\n"+point_addr;
    }

    function addPoligon(samples, ffid, point_addr) {
        let MaxPoligons = 48//ThePoligonRenderControl.size();
        if(tracesModel.count===MaxPoligons){
            let p = visualModel.items.get(0).model.idxProvider
            delProvider(p)
            let i = visualModel.items.get(0).model.index
            tracesModel.remove(i, 1)
            //            console.log("free provider:", p, "index:",i);
        }

        var provider = newProvider()
        provider.trace = samples
        provider.key_name = generate_string_key(ffid, point_addr);
        maxSamplesSize = Math.max(root.maxSamplesSize, samples.length)

        tracesModel.append( {idxProvider:provider.idx, ffid:ffid, point_addr: point_addr} )
    }


    function pushPoligon(samples, ffid, point_addr) {
        console.log("+++pushPoligon", ffid, point_addr, samples.length);

        let find_idxProvider = -1;
        for ( let i=0; i < tracesModel.count; ++i ) {
            let obj = tracesModel.get(i);
            if( ffid === obj.ffid && point_addr === obj.point_addr ){
                find_idxProvider = obj.idxProvider;
                break;
            }
        }
        if(find_idxProvider<0){
            addPoligon(samples, ffid, point_addr);
            console.log("New trace added.");
        }
        else {
            var provider = ThePoligonRenderControl.get(find_idxProvider)
            provider.trace = samples
            maxSamplesSize = Math.max(root.maxSamplesSize, samples.length)
            console.log("Poligon samples replaced.");
        }
    }


    function pushEmptyPoligon(ffid, point_addr) {
        pushPoligon(_null_samples, ffid, point_addr);
    }

    property var _null_samples: []
    Component.onCompleted: {
        for(let i=0; i<1500; ++i) _null_samples.push( 0. );
    }
}
