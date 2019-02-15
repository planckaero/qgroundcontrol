import QtQuick 2.0

Rectangle {
    id: camChooser
    color: colorBG
    width: buttonWidth
    height: buttonHeight * 3
    z: parent.z + 4 // This is important. If this control is underneath the map, we don't get touch/click input

    // Select camera to view
    readonly property int cameraNone:               0 // N/A
    readonly property int cameraDownward:           1 // Downward-facing camera
    readonly property int cameraGimbal:             2 // Gimbal camera
    property int cameraChoice:                      cameraDownward

    // Button attributes
    readonly property int buttonWidth: 60
    readonly property int buttonHeight: 40
    readonly property int buttonFontSize: 10

    // Box colors
    readonly property string colorBG:       "black"
    readonly property string colorText:     "white"
    readonly property string colorClick:    "red"
    readonly property string colorSel:      "green"
    readonly property string colorBorder:   "gray"

    Rectangle {
        id: rectCamLabel
        width: buttonWidth; height: buttonHeight
        color: colorBG
        Text {
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            color: colorText
            font.pointSize: buttonFontSize
            text: "Camera"
        }
    }

    Rectangle {
        id: rectDownward
        anchors.top: rectCamLabel.bottom
        width: buttonWidth; height: buttonHeight
        color: colorSel
        border { width: 1; color: colorBorder }
        Text {
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            color: colorText
            font.pointSize: buttonFontSize
            text: "Down"
        }
        MouseArea {
            id: mouseAreaFree
            anchors.fill: parent
            preventStealing: true
            onPressed:
            {
                parent.color = colorClick
            }
            onReleased:
            {
                cameraChoice = cameraDownward
                rectDownward.color = colorSel
                rectGimbal.color = colorBG
            }
        }
    }

    Rectangle {
        id: rectGimbal
        anchors.top: rectDownward.bottom
        width: buttonWidth; height: buttonHeight
        color: colorBG
        border { width: 1; color: colorBorder }
        Text {
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            color: colorText
            font.pointSize: buttonFontSize
            text: "Gimbal"
        }
        MouseArea {
            id: mouseAreaDrone
            anchors.fill: parent
            preventStealing: true
            onPressed:
            {
                parent.color = colorClick
            }
            onReleased:
            {
                cameraChoice = cameraGimbal
                rectGimbal.color = colorSel
                rectDownward.color = colorBG
            }
        }
    }
}
