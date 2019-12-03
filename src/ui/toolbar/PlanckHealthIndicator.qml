import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts  1.2

import QGroundControl                       1.0
import QGroundControl.Controls              1.0
import QGroundControl.ScreenTools           1.0


Item {
    width:          planckhealthRow.width * 1.1
    anchors.top:    parent.top
    anchors.bottom: parent.bottom
    visible:        true

    property bool tagHealthy: QGroundControl.planckListener.TagHealth
    property bool boatHealthy: QGroundControl.planckListener.BoatHealth

    Row {
        id:             planckhealthRow
        anchors.top:    parent.top
        anchors.bottom: parent.bottom
        spacing:        ScreenTools.defaultFontPixelWidth

        // Tag estimator health indicator
        Rectangle {
            width: 40; height: 30
            color: "transparent"

            // Visible border box
            Rectangle {
                width:  30
                height: 30
                anchors.horizontalCenter: parent.horizontalCenter
                color:  "transparent"
                border.width: 2
                border.color: tagHealthy ? "white" : "red"
            }

            // Text label
            QGCLabel {
                text:           "TAG"
                font.family:    ScreenTools.demiboldFontFamily
                font.pointSize: ScreenTools.smallFontPointSize
                anchors.fill:   parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            // Draw a diagonal line through box
            Rectangle {
                visible: !tagHealthy
                width: 40; height: 2
                color: "red"
                anchors.verticalCenter: parent.verticalCenter
                transform: Rotation { origin.x: 20; origin.y: 0; angle: 45}
            }

        }

        // Boat estimator health indicator
        Rectangle {
            width: 40; height: 30
            color: "transparent"

            // Visible border box
            Rectangle {
                width:  30
                height: 30
                anchors.horizontalCenter: parent.horizontalCenter
                color:  "transparent"
                border.width: 2
                border.color: boatHealthy ? "white" : "red"
            }

            // Text label
            QGCLabel {
                text:           "CB\nGPS"
                font.family:    ScreenTools.demiboldFontFamily
                font.pointSize: ScreenTools.smallFontPointSize
                anchors.fill:   parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            // Draw a diagonal line through box
            Rectangle {
                visible: !boatHealthy
                width: 42; height: 2
                color: "red"
                anchors.verticalCenter: parent.verticalCenter
                transform: Rotation { origin.x: 20; origin.y: 0; angle: 45}
            }
        }
    }
}
