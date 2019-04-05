
import QtQuick                  2.3
import QtQuick.Controls         1.2
import QtLocation               5.3

import QGroundControl               1.0
import QGroundControl.Controls      1.0

Rectangle {
    height:     300
    width:      300
    color:      "#000004"
    border.width:   3
    border.color:   "white"
    radius: 3
    z: parent.z+5

    property real _east_offset:         0
    property real _north_offset:        0

    MouseArea {
        anchors.fill: parent
        preventStealing: true
        enabled: true
        onPressed: {
            setpointCircle.x = mouseX - (setpointCircle.width/2)
            setpointCircle.y = mouseY - (setpointCircle.height/2)
            parent._east_offset = (mouseX - 150) / 10
            parent._north_offset = (150 - mouseY) / 10
            console.debug("Clicked:" + parent._east_offset + ":" + parent._north_offset)
        }
    }

    // Title
    Label {
        anchors.left:           parent.left
        anchors.right:          parent.right
        anchors.topMargin:      10
        wrapMode:               Text.WordWrap
        horizontalAlignment:    Text.AlignHCenter
        text:                   qsTr("Wingman Relative Position")
    }

    /// Landing Pad
    Image {
        source:         "/res/PlanckTag"
        mipmap:         true
        antialiasing:   true
        fillMode:       Image.PreserveAspectFit
        height:         40
        sourceSize.height:      height
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
    }

    // Display of setpoint offset coordinates
    Column {
        id:                 numericColumn
        anchors.right:      parent.right
        anchors.bottom:     parent.bottom
        width:  80
        height: 40

        Label {
            anchors.right:          parent.right
            anchors.rightMargin:    5
            text:                   _north_offset + "m North"
        }
        Label {
            anchors.right:          parent.right
            anchors.rightMargin:    5
            text:                   _east_offset + "m East"
        }
    }

    // Actually draws a circle, go figure
    Rectangle {
        id: setpointCircle
        width: 20
        height: width
        color: "red"
        border.color: "red"
        border.width: 1
        radius: width*0.5
        x: 150 - (width/2)
        y: 150 - (height/2)
    }

    // 10m range ring
    Rectangle {
        id: ring
        width: 200
        height: width
        color: "transparent"
        border.color: "green"
        border.width: 2
        radius: width*0.5
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Text {
        text: "10m"
        color: "white"
        anchors.bottom: ring.top
        anchors.horizontalCenter: ring.horizontalCenter
    }

} // Rectangle
