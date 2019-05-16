
// TODO: figure out which imports are necessary
import QtQuick          2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs  1.2
import QtQuick.Layouts  1.2

import QGroundControl               1.0
import QGroundControl.Controls      1.0
import QGroundControl.Palette       1.0
import QGroundControl.ScreenTools   1.0
import QGroundControl.Controllers   1.0
import QGroundControl.FactSystem    1.0
import QGroundControl.FactControls  1.0

SetupPage {
    id: planckPage
    pageComponent: planckPageComponent
    pageName: "Planck"

    Component {
        id: planckPageComponent

        Column {
            spacing: _margins
            width: availableWidth

            FactPanelController { id: controller; factPanel: planckPage.viewPanel }

            QGCPalette { id: palette; colorGroupEnabled: true }

            ListModel {
                id: tagSizeModel

                Component.onCompleted: {
                    append({"text": "Origami", "value": 0})
                    append({"text": "LARS", "value": 1})
                }
            }

            ListModel {
                id: tagLayoutModel

                Component.onCompleted: {
                    append({"text": "Nested Tag", "value": 0})
                    append({"text": "Nested Tag with Corners", "value": 1})
                }
            }

            Component {
                id: tagSettings

                Item {
                    width:  rectangle.x + rectangle.width
                    height: rectangle.y + rectangle.height

                    QGCLabel {
                        id:         tagSettingLabel
                        text:       qsTr("Tag")
                        font.family: ScreenTools.demiboldFontFamily
                    }

                    Rectangle {
                        id:                 rectangle
                        anchors.topMargin:  _margins / 2
                        anchors.left:       parent.left
                        anchors.top:        tagSettingLabel.bottom
                        width:              tagLayoutComboBox.x + tagLayoutComboBox.width + _margins
                        height:             tagLayoutComboBox.y + tagLayoutComboBox.height + _margins
                        color:              palette.windowShade

                        QGCLabel {
                            id: tagSizeLabel
                            anchors.margins:    _margins
                            anchors.left:       parent.left
                            anchors.baseline:   tagSizeCombo.baseline
                            text:               qsTr("Tag Size:")
                        }

                        QGCComboBox {
                            id: tagSizeCombo
                            anchors.top:        parent.top
                            anchors.left:       tagLayoutLabel.right
                            width:              ScreenTools.defaultFontPixelWidth * 32
                            model:              tagSizeModel
                        }

                        QGCLabel {
                            id: tagLayoutLabel
                            anchors.margins:    _margins
                            anchors.left:       parent.left
                            anchors.baseline:   tagLayoutCombo.baseline
                            text:               qsTr("Tag Layout:")
                        }

                        QGCComboBox {
                            id: tagLayoutCombo
                            anchors.top:        tagSizeCombo.bottom
                            anchors.left:       tagSizeCombo.left
                            width:              ScreenTools.defaultFontPixelWidth * 32
                            model:              tagLayoutModel
                        }
                    } // Rectangle
                } // Item
            } // Component - tagSettings

            Loader {
                id: tagSettingsLoader
                sourceComponent: tagSettings
            }
        } // Column
    } // Component
}
