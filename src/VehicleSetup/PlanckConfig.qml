
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

    Component {
        id: planckPageComponent

        Column {
            spacing: _margins
            width: availableWidth

            FactPanelController { id: controller; factPanel: planckPage.viewPanel }

            QGCPalette { id: palette; colorGroupEnabled: true }

            function _approxEqual(a, b) {
                return (Math.abs(a - b) < 1.0e-6);
            }

            // Tag Settings
            Component {
                id: tagSettings

                Item {
                    width:  rectangle.x + rectangle.width
                    height: rectangle.y + rectangle.height

                    property Fact _tagSizeLarge:      controller.getParameterFact(90, "TAG_SIZE_LARGE");
                    property Fact _tagSizeMedium:     controller.getParameterFact(90, "TAG_SIZE_MED");
                    property Fact _tagSizeSmall:      controller.getParameterFact(90, "TAG_SIZE_SMALL");
                    property Fact _tagSizeCorner:     controller.getParameterFact(90, "TAG_CORNER_SIZE");
                    property Fact _useCornerTags:     controller.getParameterFact(90, "TAG_USE_CORNERS");

                    function _modifyAllSizes(large, medium, small, corner) {
                        _tagSizeLarge.value = large;
                        _tagSizeMedium.value = medium;
                        _tagSizeSmall.value = small;
                        _tagSizeCorner.value = corner;
                    }

                    function _changeTagSizes(sizeIndex) {
                        // Origami
                        if (sizeIndex === 0) {
                            _modifyAllSizes(0.611, 0.122, 0.024, 0.061);
                        }
                        else if (sizeIndex === 1) {
                            _modifyAllSizes(0.8, 0.16, 0.032, 0.08);
                        }
                        else {
                            // TODO: trigger some sort of prompt
                            console.log("TODO: trigger custom size specification prompt");
                        }
                    }

                    function _setTagLayout(layoutIndex) {
                        console.log("_setTagLayout (" + layoutIndex + ")");
                        if (layoutIndex === 0) {
                            _useCornerTags.value = 0;
                        }
                        else if (layoutIndex === 1) {
                            _useCornerTags.value = 1;
                        }
                    }

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
                        width:              tagLayoutCombo.x + tagLayoutCombo.width + _margins
                        height:             tagLayoutCombo.y + tagLayoutCombo.height + _margins
                        color:              palette.windowShade

                        QGCLabel {
                            id:                 tagSizeLabel
                            anchors.margins:    _margins
                            anchors.left:       parent.left
                            anchors.baseline:   tagSizeCombo.baseline
                            text:               qsTr("Size: ")
                        }

                        QGCComboBox {
                            id:                 tagSizeCombo
                            anchors.margins:    _margins
                            anchors.top:        parent.top
                            anchors.left:       tagLayoutLabel.right
                            width:              ScreenTools.defaultFontPixelWidth * 32
                            model:              ListModel {
                                                    id: tagSizeModel
                                                    ListElement {text: "N/A"; value: 0}
                                                }
                            onCurrentIndexChanged: _changeTagSizes(currentIndex);

                            Component.onCompleted: {
                                if (controller.parameterExists(90, "TAG_SIZE_LARGE") &&
                                    controller.parameterExists(90, "TAG_SIZE_MED")   &&
                                    controller.parameterExists(90, "TAG_SIZE_SMALL"))
                                {
                                    tagSizeModel.clear();
                                    tagSizeModel.append({"text": "Origami", "value": "0"});
                                    tagSizeModel.append({"text": "LARS", "value": "1"});
                                    tagSizeModel.append({"text": "Custom", "value": "2"});
                                    if(_approxEqual(_tagSizeLarge.value, 0.8)   &&
                                       _approxEqual(_tagSizeMedium.value, 0.16) &&
                                       _approxEqual(_tagSizeSmall.value, 0.032))
                                    {
                                        tagSizeCombo.currentIndex = 1;
                                    }
                                    else if (_approxEqual(_tagSizeLarge.value, 0.611)  &&
                                             _approxEqual(_tagSizeMedium.value, 0.122) &&
                                             _approxEqual(_tagSizeSmall.value, 0.024))
                                    {
                                        tagSizeCombo.currentIndex = 0;
                                    }
                                    else {
                                        tagSizeCombo.currentIndex = 2;
                                    }
                                }
                                else {
                                    console.log("TAG_SIZE_LARGE not found!");
                                }
                            }
                        }

                        QGCLabel {
                            id:                     tagLayoutLabel
                            anchors.margins:        _margins
                            anchors.left:           parent.left
                            anchors.baseline:       tagLayoutCombo.baseline
                            text:                   qsTr("Layout: ")
                        }

                        QGCComboBox {
                            id:                     tagLayoutCombo
                            anchors.margins:        _margins
                            anchors.top:            tagSizeCombo.bottom
                            anchors.left:           tagLayoutLabel.right
                            width:                  ScreenTools.defaultFontPixelWidth * 32
                            model:                  ListModel {
                                                        id: tagLayoutModel
                                                        ListElement {text: "N/A"; value: 0}
                                                    }
                            onCurrentIndexChanged:  _setTagLayout(currentIndex); 

                            Component.onCompleted: {
                                if (controller.parameterExists(90, "TAG_USE_CORNERS")) {
                                    tagLayoutModel.clear();
                                    tagLayoutModel.append({"text": "Three Tag", "value": "0"});
                                    tagLayoutModel.append({"text": "Seven Tag", "value": "1"});
                                    tagLayoutCombo.currentIndex = ((_useCornerTags.value) ? 1 : 0);
                                }
                                else {
                                    console.log("TAG_USE_CORNERS NOT FOUND!");
                                }
                            }
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
