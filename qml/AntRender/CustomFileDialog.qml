import QtQuick 2.15


QtObject{
    id: root
    property string title: "fileDialog"
    property string fileUrl: ""
    property var nameFilters: ["All files (*.*)"]
    signal accepted()

    function open(){
        var dialog = FileDialogBackend.openDialog;
        dialog.nameFilters = nameFilters
        dialog.title = root.title
        dialog.accepted.connect( __accepted_function );
        dialog.rejected.connect( __rejected_function );
        dialog.open()
    }

    function __accepted_function(){
        var dialog = FileDialogBackend.openDialog;
        dialog.accepted.disconnect( __accepted_function );
        dialog.rejected.disconnect( __rejected_function );

        root.fileUrl = FileDialogBackend.stripFileUrlToPath(dialog.fileUrl);
        root.accepted()
    }

    function __rejected_function(){
        var dialog = FileDialogBackend.openDialog;
        dialog.accepted.disconnect( __accepted_function );
        dialog.rejected.disconnect( __rejected_function );
    }


}

