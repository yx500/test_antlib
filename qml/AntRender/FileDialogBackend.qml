pragma Singleton
import QtQuick 2.15


QtObject{
    id: root

    property var openDialog
    property var saveDialog

    function stripFileUrlToPath(url) {
        var urlString = url.toString();
        //    path = path.replace(/^(file:\/{2})|(qrc:\/{2})|(http:\/{2})/,""); not portable
        var s
        if (urlString.startsWith("file:///")) {
            var k = urlString.charAt(9) === ':' ? 8 : 7
            s = urlString.substring(k)
        } else {
            s = urlString
        }
        return decodeURIComponent(s);//unescape html codes like '%23' for '#'
    }

    function __createDialog(){
        var dialog;
        try{
            dialog = Qt.createQmlObject('import QtQuick.Dialogs; FileDialog {}', root, "dynamicFileDialog6")
        } catch(e){}
        if (!dialog)
            dialog = Qt.createQmlObject('import QtQuick.Dialogs 1.3; FileDialog {}', root, "dynamicFileDialog5")
        return dialog;
    }


    Component.onCompleted: {
        openDialog = __createDialog();
        saveDialog = __createDialog();
    }

}

