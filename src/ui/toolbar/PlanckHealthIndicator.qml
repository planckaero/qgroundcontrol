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

    property bool tagHealthy: QGroundControl.planckListener.tagHealth
    property bool boatHealthy: QGroundControl.planckListener.boatHealth

    Row {
        id:             planckhealthRow
        anchors.top:    parent.top
        anchors.bottom: parent.bottom
        spacing:        ScreenTools.defaultFontPixelWidth

        // Tag estimator health indicator
        Rectangle {
            width: 40; height: 30
            color: "transparent"

            Rectangle {
                width:  30
                height: 30
                anchors.horizontalCenter: parent.horizontalCenter
                color:  "transparent"
                border.width: 2
                border.color: "white"
            }

            QGCLabel {
                text:           "TAG"
                font.family:    ScreenTools.demiboldFontFamily
                font.pointSize: 10
                anchors.fill:   parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            // Draw a diagonal line through box
            Rectangle {
                visible: !tagHealthy
                width: 40; height: 2
                color: "white"
                anchors.verticalCenter: parent.verticalCenter
                transform: Rotation { origin.x: 20; origin.y: 0; angle: 45}
            }

        }

        // Boat estimator health indicator
        Rectangle {
            width: 40; height: 30
            color: "transparent"

            Rectangle {
                width:  30
                height: 30
                anchors.horizontalCenter: parent.horizontalCenter
                color:  "transparent"
                border.width: 2
                border.color: "white"
            }

            QGCLabel {
                text:           "CB\nGPS"
                font.family:    ScreenTools.demiboldFontFamily
                font.pointSize: 10
                anchors.fill:   parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            // Draw a diagonal line through box
            Rectangle {
                visible: !boatHealthy
                width: 42; height: 2
                color: "white"
                anchors.verticalCenter: parent.verticalCenter
                transform: Rotation { origin.x: 20; origin.y: 0; angle: 45}
            }
        }
    }
}
