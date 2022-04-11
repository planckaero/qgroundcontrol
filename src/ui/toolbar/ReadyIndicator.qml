/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

import QtQuick          2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts  1.2

import QGroundControl                       1.0
import QGroundControl.Controls              1.0
import QGroundControl.MultiVehicleManager   1.0
import QGroundControl.ScreenTools           1.0
import QGroundControl.Palette               1.0

//-------------------------------------------------------------------------
//-- Ready Indicator
QGCComboBox {
    function getReadyStateText() {
        //Mirror the MAV_STATE enumeration
        switch(_readyState) {
        case 0:
        case 1:
        case 2:
            return "Loading...";
        case 3:
        case 4:
            return "Ready";
        case 5:
        case 6:
        case 7:
        case 8:
            return "Error";
        }
    }

    anchors.verticalCenter: parent.verticalCenter
    alternateText:          getReadyStateText()
    model:                  [ qsTr("") ]
    font.pointSize:         ScreenTools.mediumFontPointSize
    currentIndex:           -1
    sizeToContents:         true
    normalColorsWhileDisabled: true
    enabled: false
    visible: true//_activeVehicle

    property bool showIndicator: true

    property var    _activeVehicle: QGroundControl.multiVehicleManager.activeVehicle
    property var    _readyState:    _activeVehicle ? QGroundControl.planckListener.takeoffReadyState : 0

    onActivated: {
    }
}
