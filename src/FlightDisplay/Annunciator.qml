/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

import QtQuick                  2.12
import QtQuick.Controls         2.4
import QtQuick.Dialogs          1.3
import QtQuick.Layouts          1.12

import QtLocation               5.3
import QtPositioning            5.3
import QtQuick.Window           2.2
import QtQml.Models             2.1

import QGroundControl               1.0
import QGroundControl.Controllers   1.0
import QGroundControl.Controls      1.0
import QGroundControl.FactSystem    1.0
import QGroundControl.FlightDisplay 1.0
import QGroundControl.FlightMap     1.0
import QGroundControl.Palette       1.0
import QGroundControl.ScreenTools   1.0
import QGroundControl.Vehicle       1.0

//-- Annunciator panel
Rectangle {
    id:                         _root
    color:                      qgcPal.window
    radius:                     ScreenTools.defaultFontPixelWidth / 2
    width:                      annunciatorColumns.width + _toolsMargin * 2
    height:                     annunciatorColumns.height + _toolsMargin * 2

    readonly property double    ekfHighThresh:  0.8
    readonly property double    vibeHighThresh: QGroundControl.settingsManager.flyViewSettings.vibeMaxThreshold.rawValue
    readonly property double    tiltHighThresh: QGroundControl.settingsManager.flyViewSettings.tiltMaxThreshold.rawValue

    readonly property bool isVibeNaN: isNaN(_activeVehicle.vibration.xAxis.value) || isNaN(_activeVehicle.vibration.yAxis.value)
    readonly property bool isTiltNaN: isNaN(_activeVehicle.roll.value) || isNaN(_activeVehicle.pitch.value)

    readonly property double ekfVel:  _activeVehicle && _activeVehicle.estimatorStatus.goodHorizVelEstimate.value    ? _activeVehicle.estimatorStatus.velRatio.value : -1
    readonly property double ekfHPos: _activeVehicle && _activeVehicle.estimatorStatus.goodHorizPosAbsEstimate.value ? _activeVehicle.estimatorStatus.horizPosRatio.value : -1
    readonly property double ekfVPos: _activeVehicle && _activeVehicle.estimatorStatus.goodVertPosAbsEstimate.value  ? _activeVehicle.estimatorStatus.vertPosRatio.value : -1
    readonly property double ekfTerr: _activeVehicle && _activeVehicle.estimatorStatus.goodVertPosAGLEstimate.value  ? _activeVehicle.estimatorStatus.haglRatio.value : -1
    readonly property double ekfMag:  _activeVehicle && !isNaN(_activeVehicle.estimatorStatus.magRatio.value) ?  _activeVehicle.estimatorStatus.magRatio.value : -1
    readonly property double vibe:    _activeVehicle && !isVibeNaN ?  getAbsLargestOf(_activeVehicle.vibration.xAxis.value, _activeVehicle.vibration.yAxis.value, _activeVehicle.vibration.zAxis.value) : -1
    readonly property double tilt:    _activeVehicle && !isTiltNaN ?  getAbsLargestOf(_activeVehicle.roll.value, _activeVehicle.pitch.value, 0) : -1

    property double ekfVelMax:  -1
    property double ekfHPosMax: -1
    property double ekfVPosMax: -1
    property double ekfTerrMax: -1
    property double ekfMagMax:  -1
    property double vibeMax:    -1
    property double tiltMax:    -1

    function resetMax() {
        ekfVelMax = ekfVel.valueOf()
        ekfHPosMax = ekfHPos.valueOf()
        ekfVPosMax = ekfVPos.valueOf()
        ekfMagMax = ekfMag.valueOf()
        ekfTerrMax = ekfTerr.valueOf()
        vibeMax = vibe.valueOf()
        tiltMax = tilt.valueOf()
    }

    // Update max values based on live value changes
    onEkfVelChanged: {
        let val = ekfVel.valueOf()
        if(isNaN(val)) val = -1;
        ekfVelMax = Math.max(val, ekfVelMax.valueOf())
    }
    onEkfHPosChanged: {
        let val = ekfHPos.valueOf()
        if(isNaN(val)) val = -1;
        ekfHPosMax = Math.max(val, ekfHPosMax.valueOf())
    }
    onEkfVPosChanged: {
        let val = ekfVPos.valueOf()
        if(isNaN(val)) val = -1;
        ekfVPosMax = Math.max(val, ekfVPosMax.valueOf())
    }
    onEkfTerrMaxChanged:  {
        let val = ekfTerr.valueOf()
        if(isNaN(val)) val = -1;
        ekfTerrMax = Math.max(val, ekfTerrMax.valueOf())
    }
    onEkfMagChanged: {
        let val = ekfMag.valueOf()
        if(isNaN(val)) val = -1;
        ekfMagMax = Math.max(val, ekfMagMax.valueOf())
    }
    onVibeChanged: {
        let val = vibe.valueOf()
        if(isNaN(val)) val = -1;
        vibeMax = Math.max(val, vibeMax.valueOf())
    }
    onTiltChanged: {
        let val = tilt.valueOf()
        if(isNaN(val)) val = -1;
        tiltMax = Math.max(val, tiltMax.valueOf())
    }

    function clamp(value, min, max) {
        return Math.min(max, Math.max(min, value))
    }

    //Linearly scale red & green up to the max.
    //At max/2, both red and green are 1 to make yellow
    function getColor(value, max) {
        if(value < 0) return qgcPal.colorGrey
        var redVal = Math.abs(value)/(max/2)
        var greenVal = (-Math.abs(value)/(max/2)) + 2
        return Qt.rgba(clamp(redVal,0,1), clamp(greenVal,0,1), 0, 1)
    }

    function getEKFColor(value) {
        return getColor(value, ekfHighThresh)
    }

    function getAbsLargestOf(v1, v2, v3) {
        return Math.max(Math.abs(v1),Math.abs(v2),Math.abs(v3))
    }

    RowLayout {
        id: annunciatorColumns
        anchors.verticalCenter: parent.verticalCenter
        spacing: _toolsMargin
        ColumnLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true
            QGCLabel {
                Layout.fillHeight: true
                verticalAlignment: Text.AlignVCenter
                text: "Max"
                rotation: 270
            }
            QGCLabel {
                Layout.fillHeight: true
                verticalAlignment: Text.AlignVCenter
                text: "Live"
                rotation: 270
            }
        }

        GridLayout {
            id:     annunciatorGrid
            flow: GridLayout.TopToBottom
            rows: 2
            columns: 7

            Repeater {
                id: annunciatorRepeater
                model: [
                    { text: qsTr("EKF\nVEL"),  color: getEKFColor(ekfVelMax)            },
                    { text: qsTr("EKF\nVEL"),  color: getEKFColor(ekfVel)               },
                    { text: qsTr("EKF\nHPOS"), color: getEKFColor(ekfHPosMax)           },
                    { text: qsTr("EKF\nHPOS"), color: getEKFColor(ekfHPos)              },
                    { text: qsTr("EKF\nVPOS"), color: getEKFColor(ekfVPosMax)           },
                    { text: qsTr("EKF\nVPOS"), color: getEKFColor(ekfVPos)              },
                    { text: qsTr("EKF\nMAG"),  color: getEKFColor(ekfMagMax)            },
                    { text: qsTr("EKF\nMAG"),  color: getEKFColor(ekfMag)               },
                    { text: qsTr("EKF\nTERR"), color: getEKFColor(ekfTerrMax)           },
                    { text: qsTr("EKF\nTERR"), color: getEKFColor(ekfTerr)              },
                    { text: qsTr("VIBE"),      color: getColor(vibeMax, vibeHighThresh) },
                    { text: qsTr("VIBE"),      color: getColor(vibe, vibeHighThresh)    },
                    { text: qsTr("TILT"),      color: getColor(tiltMax, tiltHighThresh) },
                    { text: qsTr("TILT"),      color: getColor(tilt, tiltHighThresh)    }
                ]

                Rectangle {
                    id:         ekfVelAnnunciator
                    width:      ScreenTools.defaultFontPixelWidth * 5
                    height:     ScreenTools.defaultFontPixelHeight * 2
                    color:      modelData.color
                    visible:    true
                    QGCLabel {
                        text:               modelData.text
                        color:              _activeVehicle ? Qt.rgba(0,0,0,1) : Qt.rgba(1,1,1,1)
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                }
            }
        }

        QGCButton {
            Layout.alignment: Qt.AlignTop
            text: "Reset"
            onClicked:resetMax()
        }
    }
}
