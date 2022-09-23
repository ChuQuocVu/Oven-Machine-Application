import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11
import QtQuick.Dialogs 1.3
import QtGraphicalEffects 1.12
import QUOCVU.Oven 1.0

Window {
    width: 850
    height: 530
    visible: true
    color: "#0d0d1e"
    title: qsTr("Oven Machine")

    Timer
    {
        id: timerId

        beginValue: 0

        onSecondChanged:
        {
            timeId.text = value + " : " + second
        }

        onValueChanged:
        {
            timeId.text = value + " : " + second
        }

        onTimeOut:
        {
            startText.text = "START"
        }

    }

    Mode
    {
        id: ovenModeId
        userMode: Mode.MANUAL
    }



    Dial {
        id: timeController
        x: 308
        y: 289
        layer.smooth: true
        font.hintingPreference: Font.PreferDefaultHinting
        font.bold: true
        snapMode: Dial.NoSnap
        wrap: true
        from: 0
        to: 200

        onMoved:
        {
            if(!timerId.isRunning)
            {
                temperatureText.text = timeController.value.toFixed(1) + " oC"
            }
            else
                runningMessage.open()
        }
    }

    ColorOverlay
    {
        anchors.fill: timeController
        source: timeController
        anchors.rightMargin: -2
        anchors.bottomMargin: 0
        anchors.leftMargin: 2
        anchors.topMargin: 0
        color: "#fcbf49"

        Text {
            id: temperatureText
            x: 50
            y: 68
            width: 84
            height: 48
            color: "#fcbf49"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 13
            font.bold: true
            font.family: "Tahoma"
            textFormat: Text.RichText
            text: "0 oC"


        }

    }

    ColumnLayout {
        id: recipeContainId
        x: 14
        y: 76
        width: 181
        height: 400

        ListView
        {
            id: recipesListView
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: RecipeModel

            delegate:
                Rectangle
            {
                height: 100
                radius: 10
                color : "#0d0d1e"
                border.color: "#fcbf49"
                width: parent.width
                RowLayout
                {
                    anchors.fill: parent
                    spacing: 10
                    RecipeImage
                    {
                        bgColor: "#0d0d1e"
                        textColor: "#fcbf49"
                        text: model.Name
                        filepath: model.FileImage
                    }
                    RoundButton
                    {
                        id: chooseButtonId
                        Layout.fillWidth: true
                        text: "Cook"
                        font.pointSize: 9
                        font.bold: true
                        font.family: "Tahoma"
                        highlighted: true
                        MessageDialog
                        {
                            id: defaultMessage
                            title: "Warning!"
                            text: "Recipes cannot be set in MANUAL mode!"
                            icon: StandardIcon.Warning
                        }
                        onClicked:
                        {
                            if(!timerId.isRunning)
                            {
                                if(ovenModeId.userMode == Mode.MANUAL)
                                {
                                    console.log("Recipes cannot be set in MANUAL mode!")
                                    defaultMessage.open()
                                }
                                else
                                {
                                    timerId.beginValue = model.CookingTime
                                    timeId.text = Math.floor(model.CookingTime/60) + " : " + timerId.beginValue % 60
                                    temperatureText.text = model.Temperature + " oC"
                                }
                            }
                            else
                            {
                                runningMessage.open()
                            }

                        }
                    }
                }
            }

        }
    }

    Rectangle {
        id: rectangle
        x: 296
        y: 76
        width: 207
        height: 99
        color: "#1b1b21"
        radius: 40
        border.color: "#000000"
        Text {
            id: timeId
            x: 6
            y: 8
            width: 195
            height: 82
            color: "#fcbf49"
            text: ovenModeId.userMode == Mode.DEFAULT? "Choose Recipes" : "0 : 0"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.Wrap
            font.pointSize: 13
            font.bold: true
            font.family: "Tahoma"
            styleColor: "#090808"
        }
    }

    RoundButton {
        id: stopButton
        x: 355
        y: 181
        width: 89
        height: 89
        radius: 50

        Text {
            id: startText
            color: "#fcbf49"
            text: qsTr("START")
            font.pointSize: 13
            font.bold: true
            font.family: "Tahoma"
            anchors.centerIn: stopButton
        }
        highlighted: true
        onClicked:
        {
            if(startText.text == "STOP")
            {
                startText.text = "START"
                timerId.stopTimer()
                timerText.text = "Timer"
            }
            else
            {
                startText.text = "STOP"
                timerId.startTimer(timerId.beginValue)
                timerText.text = "Heating..."
            }
        }


    }

    RoundButton {
        id: bonusButton
        x: 529
        y: 85
        width: 63
        height: 63
        text: "+"
        font.bold: true
        font.pointSize: 20
        font.family: "Tahoma"
        highlighted: true
        MessageDialog
        {
            id: runningMessage
            title: "The Oven is running!"
            text: "Stop the Oven to change anythings!"
            icon: StandardIcon.Warning
        }
        onClicked:
        {
            if(!timerId.isRunning)
            {
                timerId.beginValue = timerId.beginValue + 60
                timeId.text = Math.floor(timerId.beginValue/60) + " : " + (timerId.beginValue)%60
            }
            else
                runningMessage.open()
        }
    }

    Rectangle {
        id: grillRect
        x: 596
        y: 221
        width: 88
        height: 78
        color: ovenModeId.mode == Mode.Grill? "#fcbf49" : "beige"
        radius: 30
        border.color: "#000000"
        border.width: 1

        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                ovenModeId.mode = Mode.Grill
            }
        }
    }

    Rectangle {
        id: streamRect
        x: 721
        y: 221
        width: 88
        height: 78
        color: ovenModeId.mode == Mode.Stream? "#fcbf49" : "beige"
        radius: 30
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                ovenModeId.mode = Mode.Stream
            }
        }
    }

    Rectangle {
        id: fanRect
        x: 721
        y: 343
        width: 88
        height: 78
        color: ovenModeId.mode == Mode.Fan? "#fcbf49" : "beige"
        radius: 30
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                ovenModeId.mode = Mode.Fan
            }
        }
    }

    Rectangle {
        id: warmRect
        x: 596
        y: 343
        width: 88
        height: 78
        color: ovenModeId.mode == Mode.Warmer? "#fcbf49" : "beige"
        radius: 30
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                ovenModeId.mode = Mode.Warmer
            }
        }
    }

    Switch {
        id: modeSwitch
        x: 667
        y: 151
        checked: false
        padding: 6
        font.family: "Tahoma"
        checkable: true
        onCheckedChanged:
        {
            if(!timerId.isRunning)
            {
                if(modeSwitch.checked)
                    ovenModeId.userMode = Mode.DEFAULT
                else
                {
                    ovenModeId.userMode = Mode.MANUAL
                    timerId.beginValue = 0
                    timeId.text = "0 : 0"
                }
            }
            else
            {
                runningMessage.open()
            }
        }
    }

    Text {
        id: text1
        x: 764
        y: 161
        color: "#f5f4f4"
        text: qsTr("Default")
        font.pixelSize: 12
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.Wrap
        font.bold: true
        font.family: "Tahoma"
    }

    Text {
        id: timerText
        x: 378
        y: 36
        color: "#e7e4e0"
        text: qsTr("Timer")
        font.pixelSize: 17
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.bold: true
        font.family: "Tahoma"
    }

    Text {
        id: text2
        x: 601
        y: 161
        color: "#f5f4f4"
        text: qsTr("Manual")
        font.pixelSize: 12
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.Wrap
        font.bold: true
        font.family: "Tahoma"
    }

    RoundButton {
        id: addButton
        x: 26
        y: 482
        width: 158
        height: 40
        flat: false
        highlighted: true
        font.bold: true
        font.family: "Tahoma"

        Text {
            id: text3
            x: 34
            y: 12
            color: "#fcbf49"
            text: qsTr("ADD RECIPES")
            font.pixelSize: 13
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.bold: true
            font.family: "Tahoma"
        }

        onClicked:
        {
            if(!timerId.isRunning)
            {

            }
            else
                runningMessage.open()
        }

    }

    Image {
        id: image
        x: 614
        y: 239
        width: 53
        height: 42
        opacity: 1
        visible: true
        source: "Icon/Grill.png"
        clip: false
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: image1
        x: 729
        y: 228
        width: 72
        height: 64
        source: "Icon/Stream.png"
        fillMode: Image.Stretch
    }

    Image {
        id: image2
        x: 605
        y: 348
        width: 70
        height: 67
        source: "Icon/Warm.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: image3
        x: 714
        y: 346
        width: 103
        height: 70
        source: "Icon/Fan.png"
        fillMode: Image.PreserveAspectFit
    }

    Text {
        id: text4
        x: 747
        y: 305
        color: "#f9f9f8"
        text: qsTr("Stream")
        font.pixelSize: 12
        horizontalAlignment: Text.AlignHCenter
    }

    Text {
        id: text5
        x: 628
        y: 305
        width: 26
        height: 20
        color: "#ffffff"
        text: qsTr("Grill")
        font.pixelSize: 12
        horizontalAlignment: Text.AlignHCenter
    }

    Text {
        id: text6
        x: 628
        y: 427
        width: 26
        height: 20
        color: "#ffffff"
        text: qsTr("Warm")
        font.pixelSize: 12
        horizontalAlignment: Text.AlignHCenter
    }

    Text {
        id: text7
        x: 747
        y: 427
        width: 37
        height: 20
        color: "#ffffff"
        text: qsTr("Fan")
        font.pixelSize: 12
        horizontalAlignment: Text.AlignHCenter
    }

    RoundButton {
        id: minusButton
        x: 210
        y: 85
        width: 63
        height: 63
        text: "-"
        font.bold: true
        font.family: "Tahoma"
        highlighted: true
        font.pointSize: 20

        onClicked:
        {
            if(!timerId.isRunning)
            {
                if(timerId.beginValue > 0)
                {
                    timerId.beginValue -= 60
                    if(timerId.beginValue < 0) timerId.beginValue = 0
                }

                timeId.text =Math.floor(timerId.beginValue/60) + " : " + (timerId.beginValue)%60
            }
            else
                runningMessage.open()
        }
    }

    RoundButton {
        id: powerButton
        x: 17
        y: 18
        width: 33
        height: 31
        ColorOverlay
        {
            anchors.fill: powerButton
            source: powerButton
            anchors.rightMargin: -1
            anchors.bottomMargin: -1
            anchors.leftMargin: 1
            anchors.topMargin: 1
            color: "#fed281"
        }
        highlighted: true

        onClicked:
        {
            Qt.quit()
        }
    }

    Image {
        id: image4
        x: 3
        y: 13
        width: 63
        height: 44
        source: "Icon/Power.png"
        fillMode: Image.PreserveAspectFit
    }

    Text {
        id: dateandtimeText
        x: 56
        y: 18
        width: 110
        height: 34
        color: "#fcbf49"
        text: Qt.formatTime(new Date())
        font.pixelSize: 18
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        minimumPixelSize: 48
        font.bold: true
        font.family: "Tahoma"
    }
}
