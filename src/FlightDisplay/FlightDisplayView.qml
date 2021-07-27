/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

import QtQuick                  2.11
import QtQuick.Controls         2.4
import QtQuick.Dialogs          1.3
import QtQuick.Layouts          1.11

import QtLocation               5.3
import QtPositioning            5.3
import QtQuick.Window           2.2
import QtQml.Models             2.1

import QGroundControl               1.0
import QGroundControl.Airspace      1.0
import QGroundControl.Controllers   1.0
import QGroundControl.Controls      1.0
import QGroundControl.FactSystem    1.0
import QGroundControl.FlightDisplay 1.0
import QGroundControl.FlightMap     1.0
import QGroundControl.Palette       1.0
import QGroundControl.ScreenTools   1.0
import QGroundControl.Vehicle       1.0
import QGroundControl.FactControls  1.0

/// Flight Display View
Item {

    PlanMasterController {
        id: _planController
        Component.onCompleted: {
            start(true /* flyView */)
            mainWindow.planMasterControllerView = _planController
        }
    }

    property alias  guidedController:              guidedActionsController
    property bool   activeVehicleJoystickEnabled:  activeVehicle ? activeVehicle.joystickEnabled : false
    property bool   mainIsMap:                     QGroundControl.videoManager.hasVideo ? QGroundControl.loadBoolGlobalSetting(_mainIsMapKey,  true) : true
    property bool   isBackgroundDark:              mainIsMap ? (mainWindow.flightDisplayMap ? mainWindow.flightDisplayMap.isSatelliteMap : true) : true

    property var    _missionController:             _planController.missionController
    property var    _geoFenceController:            _planController.geoFenceController
    property var    _rallyPointController:          _planController.rallyPointController
    property bool   _isPipVisible:                  QGroundControl.videoManager.hasVideo ? QGroundControl.loadBoolGlobalSetting(_PIPVisibleKey, true) : false
    property bool   _useChecklist:                  QGroundControl.settingsManager.appSettings.useChecklist.rawValue && QGroundControl.corePlugin.options.preFlightChecklistUrl.toString().length
    property bool   _enforceChecklist:              _useChecklist && QGroundControl.settingsManager.appSettings.enforceChecklist.rawValue
    property bool   _checklistComplete:             activeVehicle && (activeVehicle.checkListState === Vehicle.CheckListPassed)
    property real   _margins:                       ScreenTools.defaultFontPixelWidth / 2
    property real   _pipSize:                       mainWindow.width * 0.2
    property alias  _guidedController:              guidedActionsController
    property alias  _altitudeSlider:                altitudeSlider
    property real   _toolsMargin:                   ScreenTools.defaultFontPixelWidth * 0.75
    property bool   _showAnnunciatorPanel:          QGroundControl.settingsManager.flyViewSettings.showAnnunciatorPanel.rawValue

    readonly property var       _dynamicCameras:        activeVehicle ? activeVehicle.dynamicCameras : null
    readonly property bool      _isCamera:              _dynamicCameras ? _dynamicCameras.cameras.count > 0 : false
    readonly property real      _defaultRoll:           0
    readonly property real      _defaultPitch:          0
    readonly property real      _defaultHeading:        0
    readonly property real      _defaultAltitudeAMSL:   0
    readonly property real      _defaultGroundSpeed:    0
    readonly property real      _defaultAirSpeed:       0
    readonly property string    _mapName:               "FlightDisplayView"
    readonly property string    _showMapBackgroundKey:  "/showMapBackground"
    readonly property string    _mainIsMapKey:          "MainFlyWindowIsMap"
    readonly property string    _PIPVisibleKey:         "IsPIPVisible"

    Timer {
        id:             checklistPopupTimer
        interval:       1000
        repeat:         false
        onTriggered: {
            if (visible && !_checklistComplete) {
                checklistDropPanel.open()
            }
            else {
                checklistDropPanel.close()
            }
        }
    }

    function setStates() {
        QGroundControl.saveBoolGlobalSetting(_mainIsMapKey, mainIsMap)
        if(mainIsMap) {
            //-- Adjust Margins
            _flightMapContainer.state   = "fullMode"
            _flightVideo.state          = "pipMode"
        } else {
            //-- Adjust Margins
            _flightMapContainer.state   = "pipMode"
            _flightVideo.state          = "fullMode"
        }
    }

    function setPipVisibility(state) {
        _isPipVisible = state;
        QGroundControl.saveBoolGlobalSetting(_PIPVisibleKey, state)
    }

    function isInstrumentRight() {
        if(QGroundControl.corePlugin.options.instrumentWidget) {
            if(QGroundControl.corePlugin.options.instrumentWidget.source.toString().length) {
                switch(QGroundControl.corePlugin.options.instrumentWidget.widgetPosition) {
                case CustomInstrumentWidget.POS_TOP_LEFT:
                case CustomInstrumentWidget.POS_BOTTOM_LEFT:
                case CustomInstrumentWidget.POS_CENTER_LEFT:
                    return false;
                }
            }
        }
        return true;
    }

    function showPreflightChecklistIfNeeded () {
        if (activeVehicle && !_checklistComplete && _enforceChecklist) {
            checklistPopupTimer.restart()
        }
    }

    Connections {
        target:                     _missionController
        onResumeMissionUploadFail:  guidedActionsController.confirmAction(guidedActionsController.actionResumeMissionUploadFail)
    }

    Connections {
        target:                 mainWindow
        onArmVehicle:           guidedController.confirmAction(guidedController.actionArm)
        onDisarmVehicle: {
            if (guidedController.showEmergenyStop) {
                guidedController.confirmAction(guidedController.actionEmergencyStop)
            } else {
                guidedController.confirmAction(guidedController.actionDisarm)
            }
        }
        onVtolTransitionToFwdFlight:    guidedController.confirmAction(guidedController.actionVtolTransitionToFwdFlight)
        onVtolTransitionToMRFlight:     guidedController.confirmAction(guidedController.actionVtolTransitionToMRFlight)
        onFlightDisplayMapChanged:      setStates()
    }

    Component.onCompleted: {
        if(QGroundControl.corePlugin.options.flyViewOverlay.toString().length) {
            flyViewOverlay.source = QGroundControl.corePlugin.options.flyViewOverlay
        }
        if(QGroundControl.corePlugin.options.preFlightChecklistUrl.toString().length) {
            checkList.source = QGroundControl.corePlugin.options.preFlightChecklistUrl
        }
    }

    // The following code is used to track vehicle states for showing the mission complete dialog
    property bool vehicleArmed:                     activeVehicle ? activeVehicle.armed : true // true here prevents pop up from showing during shutdown
    property bool vehicleWasArmed:                  false
    property bool vehicleInMissionFlightMode:       activeVehicle ? (activeVehicle.flightMode === activeVehicle.missionFlightMode) : false
    property bool vehicleWasInMissionFlightMode:    false
    property bool showMissionCompleteDialog:        vehicleWasArmed && vehicleWasInMissionFlightMode &&
                                                        (_missionController.containsitems || _geoFenceController.containsItems || _rallyPointController.containsItems ||
                                                        (activeVehicle ? activeVehicle.cameraTriggerPoints.count !== 0 : false))

    onVehicleArmedChanged: {
        if (vehicleArmed) {
            vehicleWasArmed = true
            vehicleWasInMissionFlightMode = vehicleInMissionFlightMode
        } else {
            if (showMissionCompleteDialog) {
                mainWindow.showComponentDialog(missionCompleteDialogComponent, qsTr("Flight Plan complete"), mainWindow.showDialogDefaultWidth, StandardButton.Close)
            }
            vehicleWasArmed = false
            vehicleWasInMissionFlightMode = false
        }
    }

    onVehicleInMissionFlightModeChanged: {
        if (vehicleInMissionFlightMode && vehicleArmed) {
            vehicleWasInMissionFlightMode = true
        }
    }

    Component {
        id: missionCompleteDialogComponent

        QGCViewDialog {
            property var activeVehicleCopy: activeVehicle
            onActiveVehicleCopyChanged:
                if (!activeVehicleCopy) {
                    hideDialog()
                }

            QGCFlickable {
                anchors.fill:   parent
                contentHeight:  column.height

                ColumnLayout {
                    id:                 column
                    anchors.margins:    _margins
                    anchors.left:       parent.left
                    anchors.right:      parent.right
                    spacing:            ScreenTools.defaultFontPixelHeight

                    QGCLabel {
                        Layout.fillWidth:       true
                        text:                   qsTr("%1 Images Taken").arg(activeVehicle.cameraTriggerPoints.count)
                        horizontalAlignment:    Text.AlignHCenter
                        visible:                activeVehicle.cameraTriggerPoints.count !== 0
                    }

                    QGCButton {
                        Layout.fillWidth:   true
                        text:               qsTr("Remove plan from vehicle")
                        visible:            !activeVehicle.connectionLost// && !activeVehicle.apmFirmware  // ArduPilot has a bug somewhere with mission clear
                        onClicked: {
                            _planController.removeAllFromVehicle()
                            hideDialog()
                        }
                    }

                    QGCButton {
                        Layout.fillWidth:   true
                        Layout.alignment:   Qt.AlignHCenter
                        text:               qsTr("Leave plan on vehicle")
                        onClicked:          hideDialog()
                    }

                    Rectangle {
                        Layout.fillWidth:   true
                        color:              qgcPal.text
                        height:             1
                    }

                    ColumnLayout {
                        Layout.fillWidth:   true
                        spacing:            ScreenTools.defaultFontPixelHeight
                        visible:            !activeVehicle.connectionLost && _guidedController.showResumeMission

                        QGCButton {
                            Layout.fillWidth:   true
                            Layout.alignment:   Qt.AlignHCenter
                            text:               qsTr("Resume Mission From Waypoint %1").arg(_guidedController._resumeMissionIndex)

                            onClicked: {
                                guidedController.executeAction(_guidedController.actionResumeMission, null, null)
                                hideDialog()
                            }
                        }

                        QGCLabel {
                            Layout.fillWidth:   true
                            wrapMode:           Text.WordWrap
                            text:               qsTr("Resume Mission will rebuild the current mission from the last flown waypoint and upload it to the vehicle for the next flight.")
                        }
                    }

                    QGCLabel {
                        Layout.fillWidth:   true
                        wrapMode:           Text.WordWrap
                        color:              qgcPal.warningText
                        text:               qsTr("If you are changing batteries for Resume Mission do not disconnect from the vehicle.")
                        visible:            _guidedController.showResumeMission
                    }
                }
            }
        }
    }

    Window {
        id:             videoWindow
        width:          !mainIsMap ? _mapAndVideo.width  : _pipSize
        height:         !mainIsMap ? _mapAndVideo.height : _pipSize * (9/16)
        visible:        false

        Item {
            id:             videoItem
            anchors.fill:   parent
        }

        onClosing: {
            _flightVideo.state = "unpopup"
            videoWindow.visible = false
        }
    }

    /* This timer will startVideo again after the popup window appears and is loaded.
     * Such approach was the only one to avoid a crash for windows users
     */
    Timer {
      id: videoPopUpTimer
      interval: 2000;
      running: false;
      repeat: false
      onTriggered: {
          // If state is popup, the next one will be popup-finished
          if (_flightVideo.state ==  "popup") {
            _flightVideo.state = "popup-finished"
          }
          QGroundControl.videoManager.startVideo()
      }
    }

    QGCMapPalette { id: mapPal; lightColors: mainIsMap ? mainWindow.flightDisplayMap.isSatelliteMap : true }

    Item {
        id:             _mapAndVideo
        anchors.fill:   parent

        //-- Map View
        Item {
            id: _flightMapContainer
            z:  mainIsMap ? _mapAndVideo.z + 1 : _mapAndVideo.z + 2
            anchors.left:   _mapAndVideo.left
            anchors.bottom: _mapAndVideo.bottom
            visible:        mainIsMap || _isPipVisible && !QGroundControl.videoManager.fullScreen
            width:          mainIsMap ? _mapAndVideo.width  : _pipSize
            height:         mainIsMap ? _mapAndVideo.height : _pipSize * (9/16)
            states: [
                State {
                    name:   "pipMode"
                    PropertyChanges {
                        target:             _flightMapContainer
                        anchors.margins:    ScreenTools.defaultFontPixelHeight
                    }
                },
                State {
                    name:   "fullMode"
                    PropertyChanges {
                        target:             _flightMapContainer
                        anchors.margins:    0
                    }
                }
            ]
            FlightDisplayViewMap {
                id:                         _fMap
                anchors.fill:               parent
                guidedActionsController:    _guidedController
                missionController:          _planController
                positionHistoryController:  _positionHistoryController
                flightWidgets:              flightDisplayViewWidgets
                rightPanelWidth:            ScreenTools.defaultFontPixelHeight * 9
                multiVehicleView:           !singleVehicleView.checked
                scaleState:                 (mainIsMap && flyViewOverlay.item) ? (flyViewOverlay.item.scaleState ? flyViewOverlay.item.scaleState : "bottomMode") : "bottomMode"
                Component.onCompleted: {
                    mainWindow.flightDisplayMap = _fMap
                    _fMap.adjustMapSize()
                }
            }
        }

        //-- Video View
        Item {
            id:             _flightVideo
            z:              mainIsMap ? _mapAndVideo.z + 2 : _mapAndVideo.z + 1
            width:          !mainIsMap ? _mapAndVideo.width  : _pipSize
            height:         !mainIsMap ? _mapAndVideo.height : _pipSize * (9/16)
            anchors.left:   _mapAndVideo.left
            anchors.bottom: _mapAndVideo.bottom
            visible:        QGroundControl.videoManager.hasVideo && (!mainIsMap || _isPipVisible)

            onParentChanged: {
                /* If video comes back from popup
                 * correct anchors.
                 * Such thing is not possible with ParentChange.
                 */
                if(parent == _mapAndVideo) {
                    // Do anchors again after popup
                    anchors.left =       _mapAndVideo.left
                    anchors.bottom =     _mapAndVideo.bottom
                    anchors.margins =    _toolsMargin
                }
            }

            states: [
                State {
                    name:   "pipMode"
                    PropertyChanges {
                        target:             _flightVideo
                        anchors.margins:    ScreenTools.defaultFontPixelHeight
                    }
                    PropertyChanges {
                        target:             _flightVideoPipControl
                        inPopup:            false
                    }
                },
                State {
                    name:   "fullMode"
                    PropertyChanges {
                        target:             _flightVideo
                        anchors.margins:    0
                    }
                    PropertyChanges {
                        target:             _flightVideoPipControl
                        inPopup:            false
                    }
                },
                State {
                    name: "popup"
                    StateChangeScript {
                        script: {
                            // Stop video, restart it again with Timer
                            // Avoiding crashes if ParentChange is not yet done
                            QGroundControl.videoManager.stopVideo()
                            videoPopUpTimer.running = true
                        }
                    }
                    PropertyChanges {
                        target:             _flightVideoPipControl
                        inPopup:            true
                    }
                },
                State {
                    name: "popup-finished"
                    ParentChange {
                        target:             _flightVideo
                        parent:             videoItem
                        x:                  0
                        y:                  0
                        width:              videoItem.width
                        height:             videoItem.height
                    }
                },
                State {
                    name: "unpopup"
                    StateChangeScript {
                        script: {
                            QGroundControl.videoManager.stopVideo()
                            videoPopUpTimer.running = true
                        }
                    }
                    ParentChange {
                        target:             _flightVideo
                        parent:             _mapAndVideo
                    }
                    PropertyChanges {
                        target:             _flightVideoPipControl
                        inPopup:             false
                    }
                }
            ]
            //-- Video Streaming
            FlightDisplayViewVideo {
                id:             videoStreaming
                anchors.fill:   parent
                visible:        QGroundControl.videoManager.isGStreamer
            }
            //-- UVC Video (USB Camera or Video Device)
            Loader {
                id:             cameraLoader
                anchors.fill:   parent
                visible:        !QGroundControl.videoManager.isGStreamer
                source:         visible ? (QGroundControl.videoManager.uvcEnabled ? "qrc:/qml/FlightDisplayViewUVC.qml" : "qrc:/qml/FlightDisplayViewDummy.qml") : ""
            }
        }

        QGCPipable {
            id:                 _flightVideoPipControl
            z:                  _flightVideo.z + 3
            width:              _pipSize
            height:             _pipSize * (9/16)
            anchors.left:       _mapAndVideo.left
            anchors.bottom:     _mapAndVideo.bottom
            anchors.margins:    ScreenTools.defaultFontPixelHeight
            visible:            QGroundControl.videoManager.hasVideo && !QGroundControl.videoManager.fullScreen && _flightVideo.state != "popup"
            isHidden:           !_isPipVisible
            isDark:             isBackgroundDark
            enablePopup:        mainIsMap
            onActivated: {
                mainIsMap = !mainIsMap
                setStates()
                _fMap.adjustMapSize()
            }
            onHideIt: {
                setPipVisibility(!state)
            }
            onPopup: {
                videoWindow.visible = true
                _flightVideo.state = "popup"
            }
            onNewWidth: {
                _pipSize = newWidth
            }
        }

        Row {
            id:                     singleMultiSelector
            anchors.topMargin:      ScreenTools.toolbarHeight + _toolsMargin
            anchors.rightMargin:    _toolsMargin
            anchors.right:          parent.right
            spacing:                ScreenTools.defaultFontPixelWidth
            z:                      _mapAndVideo.z + 4
            visible:                QGroundControl.multiVehicleManager.vehicles.count > 1 && QGroundControl.corePlugin.options.enableMultiVehicleList

            QGCRadioButton {
                id:             singleVehicleView
                text:           qsTr("Single")
                checked:        true
                textColor:      mapPal.text
            }

            QGCRadioButton {
                text:           qsTr("Multi-Vehicle")
                textColor:      mapPal.text
            }
        }

        FlightDisplayViewWidgets {
            id:                 flightDisplayViewWidgets
            z:                  _mapAndVideo.z + 4
            height:             availableHeight - (singleMultiSelector.visible ? singleMultiSelector.height + _toolsMargin : 0) - _toolsMargin
            anchors.left:       parent.left
            anchors.right:      altitudeSlider.visible ? altitudeSlider.left : parent.right
            anchors.bottom:     parent.bottom
            anchors.top:        singleMultiSelector.visible? singleMultiSelector.bottom : undefined
            useLightColors:     isBackgroundDark
            missionController:  _missionController
            visible:            singleVehicleView.checked && !QGroundControl.videoManager.fullScreen
        }

        //-------------------------------------------------------------------------
        //-- Loader helper for plugins to overlay elements over the fly view
        Loader {
            id:                 flyViewOverlay
            z:                  flightDisplayViewWidgets.z + 1
            visible:            !QGroundControl.videoManager.fullScreen
            height:             mainWindow.height - mainWindow.header.height
            anchors.left:       parent.left
            anchors.right:      altitudeSlider.visible ? altitudeSlider.left : parent.right
            anchors.bottom:     parent.bottom
        }

        MultiVehicleList {
            anchors.margins:            _toolsMargin
            anchors.top:                singleMultiSelector.bottom
            anchors.right:              parent.right
            anchors.bottom:             parent.bottom
            width:                      ScreenTools.defaultFontPixelWidth * 30
            visible:                    !singleVehicleView.checked && !QGroundControl.videoManager.fullScreen && QGroundControl.corePlugin.options.enableMultiVehicleList
            z:                          _mapAndVideo.z + 4
            guidedActionsController:    _guidedController
        }

        //-- Virtual Joystick
        Loader {
            id:                         virtualJoystickMultiTouch
            z:                          _mapAndVideo.z + 5
            width:                      parent.width  - (_flightVideoPipControl.width / 2)
            height:                     Math.min(mainWindow.height * 0.25, ScreenTools.defaultFontPixelWidth * 16)
            visible:                    (_virtualJoystick ? _virtualJoystick.value : false) && !QGroundControl.videoManager.fullScreen && !(activeVehicle ? activeVehicle.highLatencyLink : false)
            anchors.bottom:             _flightVideoPipControl.top
            anchors.bottomMargin:       ScreenTools.defaultFontPixelHeight * 2
            anchors.horizontalCenter:   flightDisplayViewWidgets.horizontalCenter
            source:                     "qrc:/qml/VirtualJoystick.qml"
            active:                     (_virtualJoystick ? _virtualJoystick.value : false) && !(activeVehicle ? activeVehicle.highLatencyLink : false)

            property bool useLightColors: isBackgroundDark
            // The default behaviour is not centralized throttle
            property bool centralizeThrottle: _virtualJoystickCentralized ? _virtualJoystickCentralized.value : false

            property Fact _virtualJoystick: QGroundControl.settingsManager.appSettings.virtualJoystick
            property Fact _virtualJoystickCentralized: QGroundControl.settingsManager.appSettings.virtualJoystickCentralized
        }

        ToolStrip {
            visible:            (activeVehicle ? activeVehicle.guidedModeSupported : true) && !QGroundControl.videoManager.fullScreen
            id:                 toolStrip

            anchors.leftMargin: isInstrumentRight() ? _toolsMargin : undefined
            anchors.left:       isInstrumentRight() ? _mapAndVideo.left : undefined
            anchors.rightMargin:isInstrumentRight() ? undefined : ScreenTools.defaultFontPixelWidth
            anchors.right:      isInstrumentRight() ? undefined : _mapAndVideo.right
            anchors.topMargin:  _toolsMargin
            anchors.top:        parent.top
            z:                  _mapAndVideo.z + 4
            maxHeight:          parent.height - toolStrip.y + (_flightVideo.visible ? (_flightVideo.y - parent.height) : 0)
            title:              qsTr("Fly")

            property bool _anyActionAvailable: _guidedController.showStartMission || _guidedController.showResumeMission || _guidedController.showChangeAlt || _guidedController.showLandAbort
            property var _actionModel: [
                {
                    title:      _guidedController.startMissionTitle,
                    text:       _guidedController.startMissionMessage,
                    action:     _guidedController.actionStartMission,
                    visible:    _guidedController.showStartMission
                },
                {
                    title:      _guidedController.continueMissionTitle,
                    text:       _guidedController.continueMissionMessage,
                    action:     _guidedController.actionContinueMission,
                    visible:    _guidedController.showContinueMission
                },
                {
                    title:      _guidedController.changeAltTitle,
                    text:       _guidedController.changeAltMessage,
                    action:     _guidedController.actionChangeAlt,
                    visible:    _guidedController.showChangeAlt
                },
                {
                    title:      _guidedController.landAbortTitle,
                    text:       _guidedController.landAbortMessage,
                    action:     _guidedController.actionLandAbort,
                    visible:    _guidedController.showLandAbort
                }
            ]

            model: [
                {
                    name:               "Checklist",
                    iconSource:         "/qmlimages/check.svg",
                    buttonVisible:      _useChecklist,
                    buttonEnabled:      _useChecklist && activeVehicle && !activeVehicle.armed,
                },
                {
                    name:               _guidedController.takeoffTitle,
                    iconSource:         "/res/takeoff.svg",
                    buttonVisible:      _guidedController.showTakeoff || !_guidedController.showLand,
                    buttonEnabled:      _guidedController.showTakeoff,
                    action:             _guidedController.actionTakeoff
                },
                {
                    name:               _guidedController.landTitle,
                    iconSource:         "/res/land.svg",
                    buttonVisible:      _guidedController.showLand && !_guidedController.showTakeoff,
                    buttonEnabled:      _guidedController.showLand,
                    action:             _guidedController.actionLand
                },
                {
                    name:               _guidedController.rtlTitle,
                    iconSource:         "/res/rtl.svg",
                    buttonVisible:      true,
                    buttonEnabled:      _guidedController.showRTL,
                    action:             _guidedController.actionRTL
                },
                {
                    name:               _guidedController.pauseTitle,
                    iconSource:         "/res/pause-mission.svg",
                    buttonVisible:      _guidedController.showPause,
                    buttonEnabled:      _guidedController.showPause,
                    action:             _guidedController.actionPause
                },
                {
                    name:               _guidedController.sendSearchTitle, // transmit track to vehicle
                    iconSource:         "/qmlimages/MapAddMission.svg",
                    buttonVisible:      true,
                    buttonEnabled:      _guidedController.showSendSearch,
                    action:             _guidedController.actionSendSearch
                },
                {
                    name:               _guidedController.raftTitle,
                    iconSource:         "/res/raft.svg",
                    buttonVisible:      true,
                    buttonEnabled:      _guidedController.showRaft,
                    action:             _guidedController.actionRaft
                },
                {
                    name:               qsTr("Action"),
                    iconSource:         "/res/action.svg",
                    buttonVisible:      _anyActionAvailable,
                    action:             -1
                }
            ]

            onClicked: {
                if(index === 0) {
                    checklistDropPanel.open()
                } else {
                    guidedActionsController.closeAll()
                    var action = model[index].action
                    if (action === -1) {
                        guidedActionList.model   = _actionModel
                        guidedActionList.visible = true
                    } else {
                        _guidedController.confirmAction(action)
                    }
                }

            }
        }

        Rectangle {
            id: _followTrack
            anchors.topMargin:          _toolsMargin
            anchors.leftMargin:         _toolsMargin
            anchors.top:                parent.top
            anchors.left:               toolStrip.right
            z:                          _mapAndVideo.z + 1
            radius:                     ScreenTools.defaultFontPixelWidth / 2
            width: ScreenTools.defaultFontPixelWidth * 19
            height: ScreenTools.defaultFontPixelHeight * 3
            color: qgcPal.colorGrey
            border { width: 1; color: "black" }

            // Follow mode parameters
            property bool paramsReady: activeVehicle ? activeVehicle.parameterManager.parametersReady : false
            property Fact followEnableFact: paramsReady ?  activeVehicle.parameterManager.getParameter(-1, "FOLL_ENABLE") : null
            property Fact offsetXFact: paramsReady ? activeVehicle.parameterManager.getParameter(-1, "FOLL_OFS_X") : null
            property Fact offsetYFact: paramsReady ? activeVehicle.parameterManager.getParameter(-1, "FOLL_OFS_Y") : null
            property Fact offsetZFact: paramsReady ? activeVehicle.parameterManager.getParameter(-1, "FOLL_OFS_Z") : null

            // Additional UI states
            property bool followEnabled: (followEnableFact !== null) ? followEnableFact.rawValue : false;
            property bool following: activeVehicle && followEnabled ? (activeVehicle.flightMode === activeVehicle.followFlightMode) : false
            property bool trackAvailable: QGroundControl.followTargetMonitor.target_available
            property var trackPosition: QGroundControl.followTargetMonitor.target_position
            property bool vehicleArmed: activeVehicle ? activeVehicle.armed : false
            property double minFollowAlt: 4

            function toggleFollowing()  {
                if(!following) {
                    activeVehicle.flightMode = activeVehicle.followFlightMode
                }
                else {
                    activeVehicle.pauseVehicle()
                }
            }

            onFollowEnabledChanged: updateValues()
            onFollowingChanged: {
                // Set Z offset to current track offset if it is enabled by FOLL_OFS_* equal to 0
                if(following && offsetZFact !== null) {
                    // TODO: use track altitude
                    //let currentOffset = activeVehicle.altitudeAMSL.rawValue - trackPosition.altitude
                    let currentOffset = activeVehicle.altitudeRelative.rawValue
                    offsetZFact.rawValue = -currentOffset
                    if(offsetXFact !== null) {
                       offsetXFact.rawValue = 0.1;
                    }
                    if(offsetYFact !== null) {
                       offsetYFact.rawValue = 0.1;
                    }
                }
                updateValues()
            }
            onTrackAvailableChanged:  updateValues()
            onVehicleArmedChanged: {
                if(vehicleArmed) {
                    if(_followTrack.offsetXFact !== null) {
                        _followTrack.offsetXFact.rawValue = 0
                    }
                    if(_followTrack.offsetYFact !== null) {
                        _followTrack.offsetYFact.rawValue = 0
                    }
                    if(_followTrack.offsetZFact !== null) {
                        _followTrack.offsetZFact.rawValue = 0
                    }
                }
            }

            function updateValues() {
                // Show following and vehicle availability
                var displayText = activeVehicle ? (following ? "Follow Engaged" : "Start Follow") : "No Vehicle"

                // If track is not available or FOLL_ENABLE is not true and not already following, show following is disabled
                if(!following && (!trackAvailable || !followEnabled) && activeVehicle) {
                    displayText = "Follow Disabled"
                }

                // Tracking status indicator
                displayText += "\n" + (trackAvailable ? "Tracking" : "No Track")
                _followTrackText.text = displayText

                // Grey - No Active Vehicle, Red - Not Tracking, Yellow - Not Following, Green - Following
                let displayColor = qgcPal.colorGrey
                if(activeVehicle) {
                    if(trackAvailable) {
                        displayColor =  followEnabled ? (following ? qgcPal.colorGreen : "yellow") : "orange"
                    }
                    else {
                        displayColor = following ? "orange" : qgcPal.colorRed
                    }
                }
                color = displayColor
            }

            Text {
                id: _followTrackText
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                color: "black"
                font.pointSize: ScreenTools.defaultFontPointSize
                text: "No Vehicle\nNo Track"
                horizontalAlignment: Text.AlignHCenter
            }

            MouseArea {
                id: _followTrackMouseArea
                anchors.fill: parent
                preventStealing: true
                enabled: activeVehicle && (_followTrack.trackAvailable || _followTrack.following)
                onReleased: {
                    _followTrack.toggleFollowing();
                }
            }

            Connections {
                target:                 QGroundControl.multiVehicleManager
                onActiveVehicleChanged: _followTrack.updateValues()
            }
        }

        Rectangle {
            id: _followVector
            anchors.topMargin:          _toolsMargin
            anchors.leftMargin:         _toolsMargin
            anchors.top:               	parent.top
            anchors.left:               _followTrack.right
            z:                          _mapAndVideo.z + 1
            width: ScreenTools.defaultFontPixelWidth * 20
            height: ScreenTools.defaultFontPixelHeight * 6
            color: qgcPal.colorGrey
            border { width: 1; color: "black" }

            Text {
                id: _followVectorTitle
                anchors.topMargin:         _toolsMargin
                anchors.top:               parent.top
                anchors.horizontalCenter:  parent.horizontalCenter
                color: "                   black"
                font.pointSize:            ScreenTools.defaultFontPointSize
                text:                      "TRACK VECTOR"
                horizontalAlignment:       Text.AlignHCenter
            }

            Text {
                id: _followVectorText
                anchors.topMargin:         _toolsMargin
                anchors.top:               _followVectorTitle.bottom
                anchors.horizontalCenter:  parent.horizontalCenter
                color:                     "black"
                font.pointSize:            ScreenTools.mediumFontPointSize
                text:                      "N: - \nE: - \nD: -"
                horizontalAlignment:       Text.AlignHCenter
            }

            function update() {
                _followVector.color = _followTrack.trackAvailable ? "white" : qgcPal.colorGrey
                if(!_followTrack.following) {
                    _followVector.color = qgcPal.colorGrey
                    _followVectorText.text = "N: - \nE: - \nD: -"
                    return
                }

                if(_followTrack.trackPosition.isValid && activeVehicle) {
                    let displayN = (_followTrack.trackPosition.latitude - activeVehicle.latitude)*111319.9

                    // Scale longitude based on latitude
                    let scale = Math.cos(_followTrack.trackPosition.latitude*Math.PI/180.0)
                    scale = Math.min(Math.max(0.1, scale), 1.0) // 0.1 < scale < 1.0
                    let displayE = (_followTrack.trackPosition.longitude - activeVehicle.longitude)*111319.9*scale

                    // TODO: use track altitude
                    //let displayD = activeVehicle.altitudeAMSL.rawValue - _followTrack.trackPosition.altitude
                    let displayD = activeVehicle.altitudeRelative.rawValue
                    _followVectorText.text = `N: ${displayN.toFixed(2)} \nE: ${displayE.toFixed(2)} \nD: ${displayD.toFixed(2)}`
                }
            }

            Connections {
                target:  _followTrack
                onFollowingChanged:      _followVector.update()
                onTrackAvailableChanged: _followVector.update()
                onTrackPositionChanged:  _followVector.update()
            }
        }

        Rectangle {
            id: _followAscend
            anchors.topMargin:          _toolsMargin
            anchors.leftMargin:         _toolsMargin
            anchors.top:                _followTrack.bottom
            anchors.left:               toolStrip.right
            z:                          _mapAndVideo.z + 1
            width:  ScreenTools.defaultFontPixelWidth * 9
            height: ScreenTools.defaultFontPixelHeight * 3
            color:  "white"
            visible: _followTrack.following
            border { width: 1; color: "black" }

            Text {
                id: _followAscendText
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                color: "black"
                font.pointSize: ScreenTools.defaultFontPointSize
                text: "ASCEND"
                horizontalAlignment: Text.AlignHCenter
            }

            MouseArea {
                id: _followAscendMouseArea
                anchors.fill: parent
                preventStealing: true
                enabled: _followTrack.following && _followTrack.offsetZFact !== null
                onReleased: {
                    // Ascend by 2 meters (assume North-East-Down)
                    if(activeVehicle && _followTrack.offsetZFact.rawValue === 0) {
                        let targetAlt = activeVehicle.altitudeRelative.rawValue
                        //if(_followTrack.trackPosition.isValid) {
                        //    targetAlt = activeVehicle.altitudeAMSL.rawValue - _followTrack.trackPosition.altitude
                        //}

                        let setAlt = -(targetAlt+2)
                        // Use minimum follow alt if target altitude + 2 is less
                        if((targetAlt+2) < _followTrack.minFollowAlt)  {
                            setAlt = -_followTrack.minFollowAlt
                        }
                        _followTrack.offsetZFact.rawValue = setAlt
                    }
                    else {
                        _followTrack.offsetZFact.rawValue = _followTrack.offsetZFact.rawValue - 2
                    }
                }
            }
        }

        Rectangle {
            id: _followDescend
            anchors.topMargin:          _toolsMargin
            anchors.leftMargin:         _toolsMargin
            anchors.top:                _followAscend.bottom
            anchors.left:               toolStrip.right
            z:                          _mapAndVideo.z + 1
            width: ScreenTools.defaultFontPixelWidth * 9
            height: ScreenTools.defaultFontPixelHeight * 3
            color:  "white"
            visible: _followTrack.following
            border { width: 1; color: "black" }

            Text {
                id: _followDescendText
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                color: "black"
                font.pointSize: ScreenTools.defaultFontPointSize
                text: "DESCEND"
                horizontalAlignment: Text.AlignHCenter
            }

            MouseArea {
                id: _followDescendMouseArea
                anchors.fill: parent
                preventStealing: true
                enabled: _followTrack.following && _followTrack.offsetZ !== null
                onReleased: {
                    let minAlt = _followTrack.minFollowAlt

                    // Descend by 2 meters (assume North-East-Down) until minAlt meters away
                    if(activeVehicle && _followTrack.offsetZFact.rawValue === 0) {
                        // Set altitude form target to relative altitude as a default
                        let targetAlt = activeVehicle.altitudeRelative.rawValue
                        // TODO: use track altitude
                        //if(_followTrack.trackPosition.isValid) {
                        //    targetAlt = activeVehicle.altitudeAMSL.rawValue - _followTrack.trackPosition.altitude
                        //}

                        let setAlt = -(targetAlt-2)
                        if (targetAlt < (minAlt+2)) {
                            setAlt = -minAlt
                        }
                        _followTrack.offsetZFact.rawValue = setAlt
                    }
                    else if((_followTrack.offsetZFact.rawValue+2) < -minAlt) {
                        _followTrack.offsetZFact.rawValue = _followTrack.offsetZFact.rawValue + 2
                    }
                    else {
                        _followTrack.offsetZFact.rawValue = -minAlt
                    }
                }
            }
        }

        Rectangle {
            id: _followOffset
            anchors.topMargin:          _toolsMargin
            anchors.leftMargin:         _toolsMargin
            anchors.top:                _followTrack.bottom
            anchors.left:               _followAscend.right
            z:                          _mapAndVideo.z + 1
            width: ScreenTools.defaultFontPixelWidth * 9
            height: ScreenTools.defaultFontPixelHeight * 3
            color:  qgcPal.colorGrey
            visible: _followTrack.following
            border { width: 1; color: "black" }

            property bool offsetEnabled: false
            property int _xOffset: 0
            property int _yOffset: 3

            onOffsetEnabledChanged: {
                if (offsetEnabled) {
                    color = "white"
                }
                else {
                    color = qgcPal.colorGrey
                }
            }

            Text {
                id: _followOffsetText
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                color: "black"
                font.pointSize: ScreenTools.defaultFontPointSize
                text: "OFFSET"
                horizontalAlignment: Text.AlignHCenter
            }

            MouseArea {
                id: _followOffsetMouseArea
                anchors.fill: parent
                preventStealing: true
                enabled: _followTrack.following && _followTrack.offsetXFact !== null && _followTrack.offsetYFact !== null
                onReleased: {
                    if (!_followOffset.offsetEnabled) {
                        _followOffset.offsetEnabled = true;
                       _followTrack.offsetXFact.rawValue = _followOffset._xOffset;
                       _followTrack.offsetYFact.rawValue = _followOffset._yOffset;
                    }
                    else {
                        _followOffset.offsetEnabled = false;
                        _followTrack.offsetXFact.rawValue = 0;
                        _followTrack.offsetYFact.rawValue = 0;
                    }
                }
            }
        }

        PositionHistoryController {
            id:                 _positionHistoryController
            missionController:  _missionController
        }

        GuidedActionsController {
            id:                         guidedActionsController
            missionController:          _missionController
            positionHistoryController:  _positionHistoryController
            confirmDialog:              guidedActionConfirm
            actionList:                 guidedActionList
            altitudeSlider:             _altitudeSlider
            z:                          _flightVideoPipControl.z + 1

            onShowStartMissionChanged: {
                if (showStartMission) {
                    confirmAction(actionStartMission)
                }
            }

            onShowContinueMissionChanged: {
                if (showContinueMission) {
                    confirmAction(actionContinueMission)
                }
            }

            onShowLandAbortChanged: {
                if (showLandAbort) {
                    confirmAction(actionLandAbort)
                }
            }

            /// Close all dialogs
            function closeAll() {
                guidedActionConfirm.visible = false
                guidedActionList.visible    = false
                altitudeSlider.visible      = false
            }
        }

        GuidedActionConfirm {
            id:                         guidedActionConfirm
            anchors.margins:            _margins
            anchors.bottom:             parent.bottom
            anchors.horizontalCenter:   parent.horizontalCenter
            guidedController:           _guidedController
            altitudeSlider:             _altitudeSlider
        }

        GuidedActionList {
            id:                         guidedActionList
            anchors.margins:            _margins
            anchors.bottom:             parent.bottom
            anchors.horizontalCenter:   parent.horizontalCenter
            guidedController:           _guidedController
        }

        //-- Altitude slider
        GuidedAltitudeSlider {
            id:                 altitudeSlider
            anchors.margins:    _margins
            anchors.right:      parent.right
            anchors.topMargin:  ScreenTools.toolbarHeight + _margins
            anchors.top:        parent.top
            anchors.bottom:     parent.bottom
            z:                  _guidedController.z
            radius:             ScreenTools.defaultFontPixelWidth / 2
            width:              ScreenTools.defaultFontPixelWidth * 10
            color:              qgcPal.window
            visible:            false
        }
    }

    //-- Annunciator panel
    Rectangle {
        visible:                    _showAnnunciatorPanel
        id:                         annunciatorPanel
        anchors.horizontalCenter:   parent.horizontalCenter
        anchors.topMargin:          _toolsMargin
        anchors.top:                parent.top
        z:                          _mapAndVideo.z + 1
        color:                      qgcPal.globalTheme === QGCPalette.Light ? QGroundControl.corePlugin.options.toolbarBackgroundLight : QGroundControl.corePlugin.options.toolbarBackgroundDark
        radius:                     ScreenTools.defaultFontPixelWidth / 2
        width:                      annunciatorRow.width + _toolsMargin * 2
        height:                     annunciatorRow.height + _toolsMargin * 2

        Row {
            id:     annunciatorRow
            spacing:    ScreenTools.defaultFontPixelWidth
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            Repeater {
                id: annunciatorRepeater
                readonly property double    ekfHighThresh:  0.8
                readonly property double    vibeHighThresh: QGroundControl.settingsManager.flyViewSettings.vibeMaxThreshold.rawValue
                readonly property double    tiltHighThresh: QGroundControl.settingsManager.flyViewSettings.tiltMaxThreshold.rawValue

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
                    if(!activeVehicle.estimatorStatus.goodHorizVelEstimate.value)       return qgcPal.colorGrey
                    return getEKFColor(activeVehicle.estimatorStatus.velRatio.value)
                }

                function getEKFHPOSColor() {
                    if(!activeVehicle.estimatorStatus.goodHorizPosAbsEstimate.value)    return qgcPal.colorGrey
                    return getEKFColor(activeVehicle.estimatorStatus.horizPosRatio.value)
                }

                function getEKFVPOSColor() {
                    if(!activeVehicle.estimatorStatus.goodVertPosAbsEstimate.value)     return qgcPal.colorGrey
                    return getEKFColor(activeVehicle.estimatorStatus.vertPosRatio.value)
                }

                function getEKFMAGColor() {
                    return getEKFColor(activeVehicle.estimatorStatus.magRatio.value)
                }

                function getEKFTerrColor() {
                    if(!activeVehicle.estimatorStatus.goodVertPosAGLEstimate.value)     return qgcPal.colorGrey
                    return getEKFColor(activeVehicle.estimatorStatus.haglRatio.value)
                }

                function getVibeColor() {
                    return getColor(
                                getAbsLargestOf(
                                    activeVehicle.vibration.xAxis.value,
                                    activeVehicle.vibration.yAxis.value,
                                    activeVehicle.vibration.zAxis.value),
                                vibeHighThresh)
                }

                function getTiltColor() {
                    return getColor(
                                getAbsLargestOf(
                                    activeVehicle.roll.value,
                                    activeVehicle.pitch.value,
                                    0),
                                tiltHighThresh)
                }

                model: [
                    {
                        text: qsTr("EKF\nVEL"),
                        color: activeVehicle ? getEKFVelColor()     : qgcPal.colorGrey
                    },
                    {
                        text: qsTr("EKF\nHPOS"),
                        color: activeVehicle ? getEKFHPOSColor()    : qgcPal.colorGrey
                    },
                    {
                        text: qsTr("EKF\nVPOS"),
                        color: activeVehicle ? getEKFVPOSColor()    : qgcPal.colorGrey
                    },
                    {
                        text: qsTr("EKF\nMAG"),
                        color: activeVehicle ? getEKFMAGColor()     : qgcPal.colorGrey
                    },
                    {
                        text: qsTr("EKF\nTERR"),
                        color: activeVehicle ? getEKFTerrColor()    : qgcPal.colorGrey
                    },
                    {
                        text: qsTr("VIBE"),
                        color: activeVehicle ? getVibeColor()       : qgcPal.colorGrey
                    },
                    {
                        text: qsTr("TILT"),
                        color: activeVehicle ? getTiltColor()       : qgcPal.colorGrey
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
                        color:              activeVehicle ? Qt.rgba(0,0,0,1) : Qt.rgba(1,1,1,1)
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                }
            }
        }
    }

    //-- Survey wind/current speed/dir
    Rectangle {
        visible:                    true
        id:                         surveyEnvironmentalData
        anchors.horizontalCenter:   parent.horizontalCenter
        anchors.topMargin:          _toolsMargin
        anchors.top:                _showAnnunciatorPanel ? annunciatorPanel.bottom : parent.top
        z:                          _mapAndVideo.z + 1
        color:                      qgcPal.globalTheme === QGCPalette.Light ? QGroundControl.corePlugin.options.toolbarBackgroundLight : QGroundControl.corePlugin.options.toolbarBackgroundDark
        radius:                     ScreenTools.defaultFontPixelWidth / 2
        width:                      surveyEnvironmentalGrid.width + _toolsMargin * 2
        height:                     surveyEnvironmentalGrid.height + _toolsMargin * 2

        GridLayout {
            id:                 surveyEnvironmentalGrid
            rows: 3
            columns: 3
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            QGCLabel {
                text:           qsTr("Wind Speed/Dir")
                visible:        true
            }

            FactTextField {
                id:                     _windSpeedTextField
                fact:                   _positionHistoryController.windSpeed
                enabled:                activeVehicle ? !activeVehicle.armed : true
                unitsLabel: "kts"
                showUnits: true
                showHelp: false
                Layout.preferredWidth: ScreenTools.defaultFontPixelWidth * 8
            }

            FactTextField {
                id:                     _windDirTextField
                fact:                   _positionHistoryController.windHeading
                enabled:                activeVehicle ? !activeVehicle.armed : true
                unitsLabel: "deg"
                showUnits: true
                showHelp: false
                Layout.preferredWidth: ScreenTools.defaultFontPixelWidth * 9
            }

            QGCLabel {
                text:           qsTr("Current Speed/Dir")
                visible:        true
            }

            FactTextField {
                id:                     _currentSpeedTextField
                fact:                   _positionHistoryController.currentSpeed
                enabled:                activeVehicle ? !activeVehicle.armed : true
                unitsLabel: "kts"
                showUnits: true
                showHelp: false
                Layout.preferredWidth: ScreenTools.defaultFontPixelWidth * 8
            }

            FactTextField {
                id:                     _currentDirTextField
                fact:                   _positionHistoryController.currentHeading
                enabled:                activeVehicle ? !activeVehicle.armed : true
                unitsLabel: "deg"
                showUnits: true
                showHelp: false
                Layout.preferredWidth: ScreenTools.defaultFontPixelWidth * 9
            }

            Rectangle {
                id:       updateMissionButton
                width:    ScreenTools.defaultFontPixelWidth * 8.5
                height:   ScreenTools.defaultFontPixelHeight * 2
                color:    qgcPal.colorGrey
                border    { width: 1; color: "black" }
                anchors.right: parent.right

                property bool updateEnabled:  activeVehicle && activeVehicle.armed && _missionController.missionItemCount > 1

                onUpdateEnabledChanged: {
                    updateMissionButton.color = (updateMissionButton.updateEnabled) ? "white" : qgcPal.colorGrey
                }

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "black"
                    font.pointSize: ScreenTools.defaultFontPointSize
                    text: "Update"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                MouseArea {
                    anchors.fill: parent
                    preventStealing: true
                    enabled: updateEnabled
                    onReleased: {
                        // Finish editing on all text fields
                        _windSpeedTextField.focus = false
                        _windDirTextField.focus = false
                        _currentSpeedTextField.focus = false
                        _currentDirTextField.focus = false

                        _positionHistoryController.send_mission(activeVehicle.coordinate, 25)
                    }
                }
            }
            // TODO: Use this when survey gets properly implemented
            // QGCLabel {
            //     text:           qsTr("Search Width")
            //     visible:        true
            // }
            // FactTextField {
            //     fact:                   _positionHistoryController.searchWidth
            //     enabled:                activeVehicle ? !vehicleArmed : true
            //     unitsLabel: "m"
            //     showUnits: true
            //     showHelp: false
            //     Layout.preferredWidth: ScreenTools.defaultFontPixelWidth * 8
            // }
        }
    }


    //-- Airspace Indicator
    Rectangle {
        id:             airspaceIndicator
        width:          airspaceRow.width + (ScreenTools.defaultFontPixelWidth * 3)
        height:         airspaceRow.height * 1.25
        color:          qgcPal.globalTheme === QGCPalette.Light ? Qt.rgba(1,1,1,0.95) : Qt.rgba(0,0,0,0.75)
        visible:        QGroundControl.airmapSupported && mainIsMap && flightPermit && flightPermit !== AirspaceFlightPlanProvider.PermitNone
        radius:         3
        border.width:   1
        border.color:   qgcPal.globalTheme === QGCPalette.Light ? Qt.rgba(0,0,0,0.35) : Qt.rgba(1,1,1,0.35)
        anchors.top:    parent.top
        anchors.topMargin: ScreenTools.toolbarHeight + (ScreenTools.defaultFontPixelHeight * 0.25)
        anchors.horizontalCenter: parent.horizontalCenter
        Row {
            id: airspaceRow
            spacing: ScreenTools.defaultFontPixelWidth
            anchors.centerIn: parent
            QGCLabel { text: airspaceIndicator.providerName+":"; anchors.verticalCenter: parent.verticalCenter; }
            QGCLabel {
                text: {
                    if(airspaceIndicator.flightPermit) {
                        if(airspaceIndicator.flightPermit === AirspaceFlightPlanProvider.PermitPending)
                            return qsTr("Approval Pending")
                        if(airspaceIndicator.flightPermit === AirspaceFlightPlanProvider.PermitAccepted || airspaceIndicator.flightPermit === AirspaceFlightPlanProvider.PermitNotRequired)
                            return qsTr("Flight Approved")
                        if(airspaceIndicator.flightPermit === AirspaceFlightPlanProvider.PermitRejected)
                            return qsTr("Flight Rejected")
                    }
                    return ""
                }
                color: {
                    if(airspaceIndicator.flightPermit) {
                        if(airspaceIndicator.flightPermit === AirspaceFlightPlanProvider.PermitPending)
                            return qgcPal.colorOrange
                        if(airspaceIndicator.flightPermit === AirspaceFlightPlanProvider.PermitAccepted || airspaceIndicator.flightPermit === AirspaceFlightPlanProvider.PermitNotRequired)
                            return qgcPal.colorGreen
                    }
                    return qgcPal.colorRed
                }
                anchors.verticalCenter: parent.verticalCenter;
            }
        }
        property var  flightPermit: QGroundControl.airmapSupported ? QGroundControl.airspaceManager.flightPlan.flightPermitStatus : null
        property string  providerName: QGroundControl.airspaceManager.providerName
    }

    //-- Checklist GUI
    Popup {
        id:             checklistDropPanel
        x:              Math.round((mainWindow.width  - width)  * 0.5)
        y:              Math.round((mainWindow.height - height) * 0.5)
        height:         checkList.height
        width:          checkList.width
        modal:          true
        focus:          true
        closePolicy:    Popup.CloseOnEscape | Popup.CloseOnPressOutside
        background: Rectangle {
            anchors.fill:  parent
            color:      Qt.rgba(0,0,0,0)
            clip:       true
        }

        Loader {
            id:         checkList
            anchors.centerIn: parent
        }

        property alias checkListItem: checkList.item

        Connections {
            target: checkList.item
            onAllChecksPassedChanged: {
                if (target.allChecksPassed)
                {
                    checklistPopupTimer.restart()
                }
            }
        }
    }

}
