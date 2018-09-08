import QtQuick                  2.3
import QtQuick.Controls         1.2
import QtQuick.Controls.Styles  1.4
import QtQuick.Dialogs          1.2
import QtQml                    2.2

import QGroundControl                   1.0
import QGroundControl.Airmap            1.0
import QGroundControl.Airspace          1.0
import QGroundControl.Controls          1.0
import QGroundControl.Palette           1.0
import QGroundControl.ScreenTools       1.0
import QGroundControl.SettingsManager   1.0

Item {
    id:                 _root
    implicitHeight:     briefRootCol.height
    implicitWidth:      briefRootCol.width
    property real baseHeight:       ScreenTools.defaultFontPixelHeight * 22
    property real baseWidth:        ScreenTools.defaultFontPixelWidth  * 40
    property var  activeVehicle:    null
    Column {
        id:             briefRootCol
        spacing:        ScreenTools.defaultFontPixelHeight * 0.25
        Rectangle {
            color:          qgcPal.windowShade
            anchors.right:  parent.right
            anchors.left:   parent.left
            height:         briefLabel.height + ScreenTools.defaultFontPixelHeight
            QGCLabel {
                id:             briefLabel
                text:           qsTr("Flight Brief")
                font.pointSize: ScreenTools.mediumFontPointSize
                font.family:    ScreenTools.demiboldFontFamily
                anchors.centerIn: parent
            }
        }
        Item { width: 1; height: ScreenTools.defaultFontPixelHeight * 0.5; }
        Flickable {
            clip:           true
            width:          baseWidth
            height:         baseHeight - buttonRow.height - ScreenTools.defaultFontPixelHeight
            contentHeight:  briefCol.height
            flickableDirection: Flickable.VerticalFlick
            Column {
                id:                 briefCol
                spacing:            ScreenTools.defaultFontPixelHeight * 0.5
                anchors.right:      parent.right
                anchors.left:       parent.left
                QGCLabel {
                    text:           qsTr("Authorizations")
                }
                Rectangle {
                    color:          qgcPal.windowShade
                    anchors.right:  parent.right
                    anchors.left:   parent.left
                    height:         authCol.height + ScreenTools.defaultFontPixelHeight
                    Column {
                        id:                 authCol
                        spacing:            ScreenTools.defaultFontPixelHeight * 0.5
                        anchors.margins:    ScreenTools.defaultFontPixelWidth
                        anchors.right:      parent.right
                        anchors.left:       parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        //-- Actual Authorization from some jurisdiction
                        Repeater {
                            visible:        activeVehicle && activeVehicle.airspaceVehicleManager.flightPlan.authorizations.count > 0
                            model:          activeVehicle ? activeVehicle.airspaceVehicleManager.flightPlan.authorizations : []
                            Column {
                                spacing:            ScreenTools.defaultFontPixelHeight * 0.5
                                anchors.right:      parent.right
                                anchors.left:       parent.left
                                QGCLabel {
                                    text:           object.name
                                    font.family:    ScreenTools.demiboldFontFamily
                                    anchors.horizontalCenter: parent.horizontalCenter
                                }
                                Rectangle {
                                    anchors.right:      parent.right
                                    anchors.left:       parent.left
                                    height:             label.height + (ScreenTools.defaultFontPixelHeight * 0.5)
                                    color: {
                                        if(object.status === AirspaceFlightAuthorization.Pending)
                                            return _colorOrange
                                        if(object.status === AirspaceFlightAuthorization.Accepted || object.status === AirspaceFlightAuthorization.AcceptedOnSubmission)
                                            return _colorGreen
                                        if(object.status === AirspaceFlightAuthorization.Rejected || object.status === AirspaceFlightAuthorization.RejectedOnSubmission)
                                            return _colorRed
                                        return _colorGray
                                    }
                                    QGCLabel {
                                        id:     label
                                        color:  _colorWhite
                                        text: {
                                            if(object.status === AirspaceFlightAuthorization.Pending)
                                                return qsTr("Authorization Pending")
                                            if(object.status === AirspaceFlightAuthorization.Accepted || object.status === AirspaceFlightAuthorization.AcceptedOnSubmission)
                                                return qsTr("Authorization Accepted")
                                            if(object.status === AirspaceFlightAuthorization.Rejected || object.status === AirspaceFlightAuthorization.RejectedOnSubmission)
                                                return qsTr("Authorization Rejected")
                                            return qsTr("Authorization Unknown")
                                        }
                                        anchors.centerIn: parent
                                    }
                                }
                            }
                        }
                        //-- Implied Authorization from no jurisdiction
                        Rectangle {
                            anchors.right:      parent.right
                            anchors.left:       parent.left
                            height:             noAuthLabel.height + (ScreenTools.defaultFontPixelHeight * 0.5)
                            visible:            activeVehicle && activeVehicle.airspaceVehicleManager.flightPlan.authorizations.count < 1
                            color: {
                                if(_flightPermit === AirspaceFlightPlanProvider.PermitPending)
                                    return _colorOrange
                                if(_flightPermit === AirspaceFlightPlanProvider.PermitAccepted || _flightPermit === AirspaceFlightPlanProvider.PermitNotRequired)
                                    return _colorGreen
                                if(_flightPermit === AirspaceFlightPlanProvider.PermitRejected)
                                    return _colorRed
                                return _colorGray
                            }
                            QGCLabel {
                                id:     noAuthLabel
                                color:  _colorWhite
                                text: {
                                    if(_flightPermit === AirspaceFlightPlanProvider.PermitPending)
                                        return qsTr("Authorization Pending")
                                    if(_flightPermit === AirspaceFlightPlanProvider.PermitAccepted)
                                        return qsTr("Authorization Accepted")
                                    if(_flightPermit === AirspaceFlightPlanProvider.PermitRejected)
                                        return qsTr("Authorization Rejected")
                                    if(_flightPermit === AirspaceFlightPlanProvider.PermitNotRequired)
                                        return qsTr("Authorization Not Required")
                                    return qsTr("Authorization Unknown")
                                }
                                anchors.centerIn: parent
                            }
                        }
                    }
                }
                Item { width: 1; height: ScreenTools.defaultFontPixelHeight * 0.25; }
                QGCLabel {
                    text:           qsTr("Rules & Compliance")
                    visible:        hasBriefRules()
                }
                ExclusiveGroup { id: ruleGroup }
                ComplianceRules {
                    text:           qsTr("Rules you may be violating")
                    rules:          violationRules
                    visible:        violationRules && violationRules.count
                    color:          _colorRed
                    exclusiveGroup: ruleGroup
                    anchors.right:  parent.right
                    anchors.left:   parent.left
                    property var violationRules: activeVehicle ? activeVehicle.airspaceVehicleManager.flightPlan.rulesViolation : null
                }
                ComplianceRules {
                    text:           qsTr("Rules needing more information")
                    rules:          infoRules
                    color:          _colorOrange
                    visible:        infoRules && infoRules.count
                    exclusiveGroup: ruleGroup
                    anchors.right:  parent.right
                    anchors.left:   parent.left
                    property var infoRules: activeVehicle ? activeVehicle.airspaceVehicleManager.flightPlan.rulesInfo : null
                }
                ComplianceRules {
                    text:           qsTr("Rules you should review")
                    rules:          reviewRules
                    color:          _colorYellow
                    visible:        reviewRules && reviewRules.count
                    exclusiveGroup: ruleGroup
                    anchors.right:  parent.right
                    anchors.left:   parent.left
                    property var reviewRules: activeVehicle ? activeVehicle.airspaceVehicleManager.flightPlan.rulesReview : null
                }
                ComplianceRules {
                    text:           qsTr("Rules you are following")
                    rules:          followRules
                    color:          _colorGreen
                    visible:        followRules && followRules.count
                    exclusiveGroup: ruleGroup
                    anchors.right:  parent.right
                    anchors.left:   parent.left
                    property var followRules: activeVehicle ? activeVehicle.airspaceVehicleManager.flightPlan.rulesFollowing : null
                }
            }
        }
        //-------------------------------------------------------------
        //-- File Flight Plan or Close
        Item { width: 1; height: ScreenTools.defaultFontPixelHeight; }
        Row {
            id:         buttonRow
            spacing: ScreenTools.defaultFontPixelWidth
            anchors.horizontalCenter: parent.horizontalCenter
            QGCButton {
                text:           qsTr("Update Plan")
                backRadius:     4
                heightFactor:   0.3333
                showBorder:     true
                enabled:        _flightPermit !== AirspaceFlightPlanProvider.PermitNone && _dirty
                visible:        planView
                width:          ScreenTools.defaultFontPixelWidth * 12
                onClicked: {
                    if(activeVehicle) {
                        _dirty = false
                        activeVehicle.airspaceVehicleManager.flightPlan.updateFlightPlan()
                    }
                }
            }
            QGCButton {
                text:           qsTr("Submit Plan")
                backRadius:     4
                heightFactor:   0.3333
                showBorder:     true
                enabled:        _flightPermit === AirspaceFlightPlanProvider.PermitAccepted || _flightPermit === AirspaceFlightPlanProvider.PermitNotRequired && !_dirty
                width:          ScreenTools.defaultFontPixelWidth * 12
                visible:        planView
                onClicked: {
                    if(activeVehicle) {
                        activeVehicle.airspaceVehicleManager.flightPlan.submitFlightPlan()
                    }
                    mainWindow.enableToolbar()
                    rootLoader.sourceComponent = null
                }
            }
            QGCButton {
                text:           qsTr("Close")
                backRadius:     4
                heightFactor:   0.3333
                showBorder:     true
                width:          ScreenTools.defaultFontPixelWidth * 12
                onClicked: {
                    mainWindow.enableToolbar()
                    rootLoader.sourceComponent = null
                }
            }
        }
    }
}
