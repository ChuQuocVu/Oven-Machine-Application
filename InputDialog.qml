import QtQuick 2.0
import QtQuick.Layouts 1.4
import QtQuick.Controls 2.4
import QtQuick.Dialogs 1.1

Item {

    id: rootId

    function openDialog()
    {
        inputDialogId.open();
    }

    property alias personNames: nametextId.text
    property alias personAges: ageboxId.value
    signal inputDialogAccepted

    MessageDialog
    {
        id: message
        title: "Success!"
        StandardButton: StandardButton.Ok
        text: nametextId.text + " has been added in list!"
    }

    Dialog
    {
        id: inputDialogId
        title: "Personal Infomation"
        x: (parent.width - width)/2
        y: (parent.height - height)/2

        parent: Overlay.overlay
        focus: true
        modal: true
        standardButtons: Dialog.Ok | Dialog.Cancel

        ColumnLayout
        {
            spacing: 20
            anchors.fill: parent
            Label
            {
                elide: "ElideRight"
                text: "Recipe' Name:"
                Layout.fillWidth: true
            }

            TextField
            {
                id: nametextId
                focus: true
                placeholderText: "Names"
                Layout.fillWidth: true
            }

            SpinBox
            {
                id: ageboxId
                editable: true
                Layout.fillWidth: true
                value: 0 // Standard value
            }

        }

        onAccepted:
        {
            console.log("Accepted enter new data!")
            rootId.inputDialogAccepted()
            message.open()
        }
        onRejected:
        {
            console.log("Rejected enter new data!")
        }

    }

}


