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
import QGroundControl.Airspace      1.0
import QGroundControl.Airmap        1.0
import QGroundControl.Controllers   1.0
import QGroundControl.Controls      1.0
import QGroundControl.FactSystem    1.0
import QGroundControl.FlightDisplay 1.0
import QGroundControl.FlightMap     1.0
import QGroundControl.Palette       1.0
import QGroundControl.ScreenTools   1.0
import QGroundControl.Vehicle       1.0

Item {
    id: _root

    // These should only be used by MainRootWindow
    property var planController:    _planController
    property var guidedController:  _guidedController

    PlanMasterController {
        id:                     _planController
        flyView:                true
        Component.onCompleted:  start()
    }

    property bool   _mainWindowIsMap:       mapControl.pipState.state === mapControl.pipState.fullState
    property bool   _isFullWindowItemDark:  _mainWindowIsMap ? mapControl.isSatelliteMap : true
    property var    _activeVehicle:         QGroundControl.multiVehicleManager.activeVehicle
    property var    _missionController:     _planController.missionController
    property var    _geoFenceController:    _planController.geoFenceController
    property var    _rallyPointController:  _planController.rallyPointController
    property real   _margins:               ScreenTools.defaultFontPixelWidth / 2
    property var    _guidedController:      guidedActionsController
    property var    _guidedActionList:      guidedActionList
    property var    _guidedAltSlider:       guidedAltSlider
    property real   _toolsMargin:           ScreenTools.defaultFontPixelWidth * 0.75
    property rect   _centerViewport:        Qt.rect(0, 0, width, height)
    property real   _rightPanelWidth:       ScreenTools.defaultFontPixelWidth * 30
    property var    _mapControl:            mapControl

    property real   _fullItemZorder:    0
    property real   _pipItemZorder:     QGroundControl.zOrderWidgets

    property bool _showAnnunciatorPanel: QGroundControl.settingsManager.flyViewSettings.showAnnunciatorPanel.rawValue

    function _calcCenterViewPort() {
        var newToolInset = Qt.rect(0, 0, width, height)
        toolstrip.adjustToolInset(newToolInset)
        if (QGroundControl.corePlugin.options.instrumentWidget) {
            flightDisplayViewWidgets.adjustToolInset(newToolInset)
        }
    }

    QGCToolInsets {
        id:                     _toolInsets
        leftEdgeBottomInset:    _pipOverlay.visible ? _pipOverlay.x + _pipOverlay.width : 0
        bottomEdgeLeftInset:    _pipOverlay.visible ? parent.height - _pipOverlay.y : 0
    }

    FlyViewWidgetLayer {
        id:                     widgetLayer
        anchors.top:            parent.top
        anchors.bottom:         parent.bottom
        anchors.left:           parent.left
        anchors.right:          guidedAltSlider.visible ? guidedAltSlider.left : parent.right
        z:                      _fullItemZorder + 1
        parentToolInsets:       _toolInsets
        mapControl:             _mapControl
        visible:                !QGroundControl.videoManager.fullScreen
    }

    FlyViewCustomLayer {
        id:                 customOverlay
        anchors.fill:       widgetLayer
        z:                  _fullItemZorder + 2
        parentToolInsets:   widgetLayer.totalToolInsets
        mapControl:         _mapControl
        visible:            !QGroundControl.videoManager.fullScreen
    }

    GuidedActionsController {
        id:                 guidedActionsController
        missionController:  _missionController
        actionList:         _guidedActionList
        altitudeSlider:     _guidedAltSlider
    }

    /*GuidedActionConfirm {
        id:                         guidedActionConfirm
        anchors.margins:            _margins
        anchors.bottom:             parent.bottom
        anchors.horizontalCenter:   parent.horizontalCenter
        z:                          QGroundControl.zOrderTopMost
        guidedController:           _guidedController
        altitudeSlider:             _guidedAltSlider
    }*/

    GuidedActionList {
        id:                         guidedActionList
        anchors.margins:            _margins
        anchors.bottom:             parent.bottom
        anchors.horizontalCenter:   parent.horizontalCenter
        z:                          QGroundControl.zOrderTopMost
        guidedController:           _guidedController
    }

    //-- Altitude slider
    GuidedAltitudeSlider {
        id:                 guidedAltSlider
        anchors.margins:    _toolsMargin
        anchors.right:      parent.right
        anchors.top:        parent.top
        anchors.bottom:     parent.bottom
        z:                  QGroundControl.zOrderTopMost
        radius:             ScreenTools.defaultFontPixelWidth / 2
        width:              ScreenTools.defaultFontPixelWidth * 10
        color:              qgcPal.window
        visible:            false
    }

    //-- Annunciator panel
    Rectangle {
        visible:                    _showAnnunciatorPanel
        id:                         annunciatorPanel
        anchors.horizontalCenter:   parent.horizontalCenter
        anchors.topMargin:          _toolsMargin
        anchors.top:                parent.top
        z:                          QGroundControl.zOrderTopMost
        color:                      qgcPal.window
        radius:                     ScreenTools.defaultFontPixelWidth / 2
        width:                      annunciatorGrid.width + _toolsMargin * 2
        height:                     annunciatorGrid.height + _toolsMargin * 2

        GridLayout {
                id:     annunciatorGrid
                //spacing:    ScreenTools.defaultFontPixelWidth
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: _toolsMargin
                flow: GridLayout.LeftToRight
                rows: 2
                columns: 7

                Repeater {
                    id: annunciatorRepeater
                    readonly property double    ekfHighThresh:  0.8
                    readonly property double    vibeHighThresh: QGroundControl.settingsManager.flyViewSettings.vibeMaxThreshold.rawValue
                    readonly property double    tiltHighThresh: QGroundControl.settingsManager.flyViewSettings.tiltMaxThreshold.rawValue

                    property double ekfVelMax: 0
                    property double ekfHPOSMax: 0
                    property double ekfVPOSMax: 0
                    property double ekfMagMax: 0
                    property double ekfTerrMax: 0
                    property double vibeMax: 0
                    property double tiltMax: 0

                    function resetMax() {
                        print("Calling reset")
                        ekfVelMax = 0
                        ekfHPOSMax = 0
                        ekfVPOSMax = 0
                        ekfMagMax = 0
                        ekfTerrMax = 0
                        vibeMax = 0
                        tiltMax = 0
                    }

                    function clamp(value, min, max) {
                        return Math.min(max, Math.max(min, value))
                    }

                    //Linearly scale red & green up to the max.
                    //At max/2, both red and green are 1 to make yellow
                    function getColor(value, max) {
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

                    function getEKFVelColor() {
                        if(!_activeVehicle.estimatorStatus.goodHorizVelEstimate.value)       return qgcPal.colorGrey
                        return getEKFColor(_activeVehicle.estimatorStatus.velRatio.value)
                    }

                    function getEKFVelColorMax() {
                        if(!_activeVehicle.estimatorStatus.goodHorizVelEstimate.value)       return qgcPal.colorGrey
                        ekfVelMax = getAbsLargestOf(ekfVelMax, _activeVehicle.estimatorStatus.velRatio.value, 0)
                        return getEKFColor(ekfVelMax)
                    }

                    function getEKFHPOSColor() {
                        if(!_activeVehicle.estimatorStatus.goodHorizPosAbsEstimate.value)    return qgcPal.colorGrey
                        return getEKFColor(_activeVehicle.estimatorStatus.horizPosRatio.value)
                    }

                    function getEKFHPOSColorMax() {
                        if(!_activeVehicle.estimatorStatus.goodHorizPosAbsEstimate.value)    return qgcPal.colorGrey
                        ekfHPOSMax = getAbsLargestOf(ekfHPOSMax, _activeVehicle.estimatorStatus.horizPosRatio.value, 0)
                        return getEKFColor(ekfHPOSMax)
                    }

                    function getEKFVPOSColor() {
                        if(!_activeVehicle.estimatorStatus.goodVertPosAbsEstimate.value)     return qgcPal.colorGrey
                        return getEKFColor(_activeVehicle.estimatorStatus.vertPosRatio.value)
                    }

                    function getEKFVPOSColorMax() {
                        if(!_activeVehicle.estimatorStatus.goodVertPosAbsEstimate.value)    return qgcPal.colorGrey
                        ekfVPOSMax = getAbsLargestOf(ekfVPOSMax, _activeVehicle.estimatorStatus.vertPosRatio.value, 0)
                        return getEKFColor(ekfVPOSMax)
                    }

                    function getEKFMAGColor() {
                        return getEKFColor(_activeVehicle.estimatorStatus.magRatio.value)
                    }

                    function getEKFMAGColorMax() {
                        ekfMagMax = getAbsLargestOf(ekfMagMax, _activeVehicle.estimatorStatus.magRatio.value, 0)
                        return getEKFColor(ekfMagMax)
                    }

                    function getEKFTerrColor() {
                        if(!_activeVehicle.estimatorStatus.goodVertPosAGLEstimate.value)     return qgcPal.colorGrey
                        return getEKFColor(_activeVehicle.estimatorStatus.haglRatio.value)
                    }

                    function getEKFTerrColorMax() {
                        if(!_activeVehicle.estimatorStatus.goodVertPosAGLEstimate.value)     return qgcPal.colorGrey
                        ekfTerrMax = getAbsLargestOf(ekfTerrMax, _activeVehicle.estimatorStatus.haglRatio.value, 0)
                        return getEKFColor(ekfTerrMax)
                    }

                    function getVibeColor() {
                        var largestVibe = getAbsLargestOf(
                                     _activeVehicle.vibration.xAxis.value,
                                     _activeVehicle.vibration.yAxis.value,
                                     _activeVehicle.vibration.zAxis.value)
                        return getColor(largestVibe, vibeHighThresh)
                    }

                    function getVibeColorMax() {
                        var largestVibe = getAbsLargestOf(
                                     _activeVehicle.vibration.xAxis.value,
                                     _activeVehicle.vibration.yAxis.value,
                                     _activeVehicle.vibration.zAxis.value)
                        vibeMax = getAbsLargestOf(largestVibe, vibeMax, 0)
                        return getColor(vibeMax, vibeHighThresh)
                    }

                    function getTiltColor() {
                        var largestTilt = getAbsLargestOf(_activeVehicle.roll.value, _activeVehicle.pitch.value, 0)
                        return getColor(largestTilt, tiltHighThresh)
                    }

                    function getTiltColorMax() {
                        var largestTilt = getAbsLargestOf(_activeVehicle.roll.value, _activeVehicle.pitch.value, 0)
                        tiltMax = getAbsLargestOf(tiltMax, largestTilt, 0)
                        return getColor(tiltMax, tiltHighThresh)
                    }

                    model: [
                        {
                            text: qsTr("EKF\nVEL"),
                            color: _activeVehicle ? getEKFVelColor()     : qgcPal.colorGrey
                        },
                        {
                            text: qsTr("EKF\nHPOS"),
                            color: _activeVehicle ? getEKFHPOSColor()    : qgcPal.colorGrey
                        },
                        {
                            text: qsTr("EKF\nVPOS"),
                            color: _activeVehicle ? getEKFVPOSColor()    : qgcPal.colorGrey
                        },
                        {
                            text: qsTr("EKF\nMAG"),
                            color: _activeVehicle ? getEKFMAGColor()     : qgcPal.colorGrey
                        },
                        {
                            text: qsTr("EKF\nTERR"),
                            color: _activeVehicle ? getEKFTerrColor()    : qgcPal.colorGrey
                        },
                        {
                            text: qsTr("VIBE"),
                            color: _activeVehicle ? getVibeColor()       : qgcPal.colorGrey
                        },
                        {
                            text: qsTr("TILT"),
                            color: _activeVehicle ? getTiltColorMax()       : qgcPal.colorGrey
                        },
                        {
                            text: qsTr("EKF\nVEL"),
                            color: _activeVehicle ? getEKFVelColor()     : qgcPal.colorGrey
                        },
                        {
                            text: qsTr("EKF\nHPOS"),
                            color: _activeVehicle ? getEKFHPOSColor()    : qgcPal.colorGrey
                        },
                        {
                            text: qsTr("EKF\nVPOS"),
                            color: _activeVehicle ? getEKFVPOSColor()    : qgcPal.colorGrey
                        },
                        {
                            text: qsTr("EKF\nMAG"),
                            color: _activeVehicle ? getEKFMAGColor()     : qgcPal.colorGrey
                        },
                        {
                            text: qsTr("EKF\nTERR"),
                            color: _activeVehicle ? getEKFTerrColor()    : qgcPal.colorGrey
                        },
                        {
                            text: qsTr("VIBE"),
                            color: _activeVehicle ? getVibeColor()       : qgcPal.colorGrey
                        },
                        {
                            text: qsTr("TILT"),
                            color: _activeVehicle ? getTiltColor()       : qgcPal.colorGrey
                        }
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
    }

    FlyViewMap {
        id:                     mapControl
        planMasterController:   _planController
        rightPanelWidth:        ScreenTools.defaultFontPixelHeight * 9
        pipMode:                !_mainWindowIsMap
        toolInsets:             customOverlay.totalToolInsets
        mapName:                "FlightDisplayView"
    }

    FlyViewVideo {
        id: videoControl
    }

    QGCPipOverlay {
        id:                     _pipOverlay
        anchors.left:           parent.left
        anchors.bottom:         parent.bottom
        anchors.margins:        _toolsMargin
        item1IsFullSettingsKey: "MainFlyWindowIsMap"
        item1:                  mapControl
        item2:                  QGroundControl.videoManager.hasVideo ? videoControl : null
        fullZOrder:             _fullItemZorder
        pipZOrder:              _pipItemZorder
        show:                   !QGroundControl.videoManager.fullScreen &&
                                    (videoControl.pipState.state === videoControl.pipState.pipState || mapControl.pipState.state === mapControl.pipState.pipState)
    }
}
