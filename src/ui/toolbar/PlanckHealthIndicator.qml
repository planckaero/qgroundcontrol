import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts  1.2

import QGroundControl                       1.0
import QGroundControl.Controls              1.0
import QGroundControl.MultiVehicleManager   1.0
import QGroundControl.ScreenTools           1.0
import QGroundControl.Palette               1.0


Item {
    width:          planckhealthRow.width * 1.1
    anchors.top:    parent.top
    anchors.bottom: parent.bottom
    visible:        true

    property bool tagHealthy: false
    property bool boatHealthy: false

    Row {
        id:             planckhealthRow
        anchors.top:    parent.top
        anchors.bottom: parent.bottom
        spacing:        ScreenTools.defaultFontPixelWidth

        Rectangle {
            width:  45
            height: 30
            color:  tagHealthy ? "green" : "red"
            Text {
                text: "TAG"
                font.bold: true
                color: tagHealthy ? "white" : "black"
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        Rectangle {
            width:  45
            height: 30
            color:  boatHealthy ? "green" : "red"
            Text {
                text: "BOAT"
                font.bold: true
                color: boatHealthy ? "white" : "black"
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }
}
