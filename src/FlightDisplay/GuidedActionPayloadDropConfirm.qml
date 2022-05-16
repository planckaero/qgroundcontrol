/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

import QtQuick          2.12
import QtQuick.Controls 2.4
import QtQuick.Layouts  1.12

import QGroundControl               1.0
import QGroundControl.ScreenTools   1.0
import QGroundControl.Controls      1.0
import QGroundControl.Palette       1.0

Rectangle {
    id:                     _root
    width:                  mainLayout.width + (_margins * 2)
    height:                 mainLayout.height + (_margins * 2)
    radius:                 ScreenTools.defaultFontPixelWidth / 2
    color:                  "#80000000"
    visible:                false

    property var    guidedController
    property string title:              guidedController.payloadDropTitle
    property alias  message:            messageText.text
    property int    action:             guidedController.actionPayloadDrop
    property var    actionData
    property bool   hideTrigger:        false
    property var    mapIndicator

    property real _margins:         ScreenTools.defaultFontPixelWidth / 2

    Component.onCompleted: {
        guidedController.payloadDropConfirmDialog = this
        message = guidedController.payloadDropMessage
    }

    onHideTriggerChanged: {
        if (hideTrigger) {
            confirmCancelled()
        }
    }

    function show(immediate) {
        if (immediate) {
            visible = true
        } else {
            // We delay showing the confirmation for a small amount in order for any other state
            // changes to propogate through the system. This way only the final state shows up.
            visibleTimer.restart()
        }
    }

    function confirmCancelled() {
        visible = false
        hideTrigger = false
        visibleTimer.stop()
        if (mapIndicator) {
            mapIndicator.actionCancelled()
            mapIndicator = undefined
        }
    }

    Timer {
        id:             visibleTimer
        interval:       1000
        repeat:         false
        onTriggered:    visible = true
    }

    QGCPalette { id: qgcPal }

    ColumnLayout {
        id:                         mainLayout
        anchors.horizontalCenter:   parent.horizontalCenter
        spacing:                    _margins

        QGCLabel {
            id:                     messageText
            Layout.fillWidth:       true
            horizontalAlignment:    Text.AlignHCenter
            wrapMode:               Text.WordWrap
        }

        QGCCheckBox {
            id:                 optionCheckBox
            Layout.alignment:   Qt.AlignHCenter
            text:               ""
            visible:            text !== ""
        }

        RowLayout {
            Layout.alignment:       Qt.AlignHCenter
            spacing:                ScreenTools.defaultFontPixelWidth

            SliderSwitch {
                id:                     slider
                confirmText:            qsTr("Slide to confirm")
                Layout.minimumWidth:    Math.max(implicitWidth, ScreenTools.defaultFontPixelWidth * 30)

                onAccept: {
                    _root.visible = false
                    hideTrigger = false
                    guidedController.executeAction(_root.action, _root.actionData)
                    if (mapIndicator) {
                        mapIndicator.actionConfirmed()
                        mapIndicator = undefined
                    }
                }
            }

            Rectangle {
                height: slider.height * 0.75
                width:  height
                radius: height / 2
                color:  qgcPal.primaryButton

                QGCColoredImage {
                    anchors.margins:    parent.height / 4
                    anchors.fill:       parent
                    source:             "/res/XDelete.svg"
                    fillMode:           Image.PreserveAspectFit
                    color:              qgcPal.text
                }

                QGCMouseArea {
                    fillItem:   parent
                    onClicked:  confirmCancelled()
                }
            }
        }
    }
}

