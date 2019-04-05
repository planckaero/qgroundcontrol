
import QtQuick                  2.3
import QtQuick.Controls         1.2

import QGroundControl               1.0
import QGroundControl.Controls      1.0
import QGroundControl.Vehicle       1.0

/// Display small window to select wingman offset from vehicle
Map {
    id:                 _root
    zoomLevel:          QGroundControl.flightMapZoom
    center:             QGroundControl.flightMapPosition
    height:     50
    width:      50

    property real _east_offset:         5
    property real _north_offset:        5

    /*MouseArea {

    }*/

    QGCLabel {
        anchors.left:           parent.left
        anchors.right:          parent.right
        wrapMode:               Text.WordWrap
        horizontalAlignment:    Text.AlignHCenter
        text:                   qsTr("Wingman Relative Position")
    }

    /// Landing Pad
    MapQuickItem {
        anchors.center: parent.center
        anchorPoint.x:  sourceItem.width / 2
        anchorPoint.y:  sourceItem.height / 2
        visible:        gcsPosition.isValid
        coordinate:     gcsPosition

        sourceItem: Image {
            source:         "/res/PlanckTag"
            mipmap:         true
            antialiasing:   true
            fillMode:       Image.PreserveAspectFit
            height:         20
            sourceSize.height: height
        }
    }

    Column {
        id:                 numericColumn
        anchors.margins:    _margins
        anchors.top:        parent.top
        anchors.left:       parent.left
        anchors.right:      parent.right

        QGCLabel {
            id:                         northField
            anchors.horizontalCenter:   parent.horizontalCenter
            text:                       _north_offset + "m North"
        }
        QGCLabel {
            id:                         eastField
            anchors.horizontalCenter:   parent.horizontalCenter
            text:                       _east_offset + "m East"
        }
    }

    /*QGCSlider {
        id:                 altSlider
        anchors.margins:    _margins
        anchors.top:        headerColumn.bottom
        anchors.bottom:     parent.bottom
        anchors.left:       parent.left
        anchors.right:      parent.right
        orientation:        Qt.Vertical
        minimumValue:       -1
        maximumValue:       1
        zeroCentered:       true
        rotation:           180

        // We want slide up to be positive values
        transform: Rotation {
            origin.x:   altSlider.width / 2
            origin.y:   altSlider.height / 2
            angle:      180
        }
    }*/




}
