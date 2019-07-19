
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
                return (Math.abs(a - b) < 1e-5);
            }

            // Tag Settings
            Component {
                id: tagSettings

                Item {
                    width:  rectangle.x + rectangle.width
                    height: rectangle.y + rectangle.height

                    // Tag Models
                    property var _tagSizes:           [
                        {name: "Origami", large: 0.611, medium: 0.122, small: 0.024, corner: 0.0611},
                        {name: "LARS",    large: 0.8,   medium: 0.16,  small: 0.032, corner: 0.08},
                    ];
                    property var _tagLayouts:         [
                        {name: "3-Tag"},
                        {name: "7-Tag"}
                    ];

                    // Tag Parameters
                    property Fact _tagSizeLarge:      Fact{}
                    property Fact _tagSizeMedium:     Fact{}
                    property Fact _tagSizeSmall:      Fact{}
                    property Fact _tagSizeCorner:     Fact{}
                    property Fact _useCornerTags:     Fact{}

                    // Configuration Indices
                    property bool _tagSizesLoaded:    false;
                    property bool _tagLayoutsLoaded:   false;

                    // UI Callbacks
                    function _changeTagSizes(sizeIndex) {
                        if (!_tagSizesLoaded) return;
                        _tagSizeLarge.value = _tagSizes[sizeIndex].large;
                        _tagSizeMedium.value = _tagSizes[sizeIndex].medium;
                        _tagSizeSmall.value = _tagSizes[sizeIndex].small;
                        _tagSizeCorner.value = _tagSizes[sizeIndex].corner;
                    }

                    function _setTagLayout(layoutIndex) {
                        if (!_tagLayoutsLoaded) return;
                        _useCornerTags.value = layoutIndex;
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
                            model:              ListModel { id: tagSizeModel; ListElement{text: "N/A"; value: -1} }
                            onCurrentIndexChanged: _changeTagSizes(currentIndex);

                            Component.onCompleted: {
                                if (controller.parameterExists(90, "TAG_SIZE_LARGE") &&
                                    controller.parameterExists(90, "TAG_SIZE_MED")   &&
                                    controller.parameterExists(90, "TAG_SIZE_SMALL"))
                                {
                                    tagSizeModel.clear();
                                    _tagSizeLarge = controller.getParameterFact(90, "TAG_SIZE_LARGE")
                                    _tagSizeMedium = controller.getParameterFact(90, "TAG_SIZE_MED")
                                    _tagSizeSmall = controller.getParameterFact(90, "TAG_SIZE_SMALL")
                                    if (controller.parameterExists(90, "TAG_CORNER_SIZE")) {
                                        _tagSizeCorner = controller.getParameterFact(90, "TAG_CORNER_SIZE");
                                    }
                                    _tagSizesLoaded = true;
                                    var customSizes = true;
                                    for (var i = 0; i < _tagSizes.length; ++i) {
                                        tagSizeModel.append({"text": _tagSizes[i].name, "value": i});
                                        if(_approxEqual(_tagSizeLarge.value, _tagSizes[i].large)   &&
                                           _approxEqual(_tagSizeMedium.value, _tagSizes[i].medium) &&
                                           _approxEqual(_tagSizeSmall.value, _tagSizes[i].small))
                                        {
                                            customSizes = false;
                                            tagSizeCombo.currentIndex = i;
                                        }
                                    }
                                    if (customSizes) {
                                        var customIndex = _tagSizes.length;
                                        tagSizeModel.append({"text": "Custom", "value": customIndex});
                                        _tagSizes.push({name: "Custom",
                                                        large: _tagSizeLarge.value,
                                                        medium: _tagSizeMedium.value,
                                                        small: _tagSizeSmall.value,
                                                        corner: _tagSizeCorner.value});
                                        tagSizeCombo.currentIndex = customIndex;
                                    }
                                }
                                else {
                                    console.log("TAG_SIZE_LARGE NOT FOUND!");
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
                            model:                  ListModel { id: tagLayoutModel; ListElement{text: "N/A"; value: -1} }
                            onCurrentIndexChanged:  _setTagLayout(currentIndex);

                            Component.onCompleted: {
                                if (controller.parameterExists(90, "TAG_USE_CORNERS")) {
                                    tagLayoutModel.clear();
                                    _useCornerTags = controller.getParameterFact(90, "TAG_USE_CORNERS");
                                    _tagLayoutsLoaded = true;
                                    for (var i = 0; i < _tagSizes.length; ++i) {
                                        tagLayoutModel.append({"text": _tagLayouts[i].name, "value": i});
                                    }
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

            // Camera Settings
            Component {
                id: cameraSettings

                Item {
                    width:  rectangle.x + rectangle.width
                    height: rectangle.y + rectangle.height

                    property Fact _exposure:       Fact{}
                    property Fact _minExposure:    Fact{}
                    property Fact _maxExposure:    Fact{}
                    property Fact _xOffset:        Fact{}
                    property Fact _yOffset:        Fact{}
                    property Fact _zOffset:        Fact{}
                    property Fact _phiOffset:      Fact{}
                    property Fact _thetaOffset:    Fact{}
                    property Fact _psiOffset:      Fact{}

                    QGCLabel {
                        id:         cameraSettingLabel
                        text:       qsTr("Camera")
                        font.family: ScreenTools.demiboldFontFamily
                    }

                    Rectangle {
                        id:                 rectangle
                        anchors.topMargin:  _margins / 2
                        anchors.left:       parent.left
                        anchors.top:        cameraSettingLabel.bottom
                        width:              maxExposureText.x + maxExposureText.width + _margins
                        height:             psiOffsetText.y + psiOffsetText.height + _margins
                        color:              palette.windowShade

                        // Exposure Settings
                        QGCLabel {
                            id:                     exposureLabel
                            anchors.margins:        _margins
                            anchors.left:           parent.left
                            anchors.top:            parent.top
                            text:                   qsTr("Exposure")
                        }

                        QGCLabel {
                            id:                     initExposureLabel
                            anchors.margins:        _margins
                            anchors.left:           parent.left
                            anchors.baseline:       initExposureText.baseline
                            text:                   qsTr("Initial: ")
                        }

                        FactTextField {
                            id:                     initExposureText
                            anchors.margins:        _margins
                            anchors.top:            exposureLabel.bottom
                            anchors.left:           initExposureLabel.right
                            fact:                   _exposure
                            enabled:                controller.parameterExists(90, "EXPOSURE")

                            Component.onCompleted:  {
                                if (initExposureText.enabled) {
                                    _exposure = controller.getParameterFact(90, "EXPOSURE");
                                }
                            }
                        }

                        QGCLabel {
                            id:                     minExposureLabel
                            anchors.margins:        _margins
                            anchors.left:           initExposureText.right
                            anchors.baseline:       minExposureText.baseline
                            text:                   qsTr("Minimum: ")
                        }

                        FactTextField {
                            id:                     minExposureText
                            anchors.margins:        _margins
                            anchors.top:            exposureLabel.bottom
                            anchors.left:           minExposureLabel.right
                            validator:              IntValidator{ bottom: 1; top: 5000; }
                            fact:                   _minExposure
                            enabled:                controller.parameterExists(90, "MIN_EXPOSURE")

                            Component.onCompleted:  {
                                if (minExposureText.enabled) {
                                    _minExposure = controller.getParameterFact(90, "MIN_EXPOSURE");
                                }
                            }
                        }

                        QGCLabel {
                            id:                     maxExposureLabel
                            anchors.margins:        _margins
                            anchors.left:           minExposureText.right
                            anchors.baseline:       maxExposureText.baseline
                            text:                   qsTr("Maximum: ")
                        }

                        FactTextField {
                            id:                     maxExposureText
                            anchors.margins:        _margins
                            anchors.top:            exposureLabel.bottom
                            anchors.left:           maxExposureLabel.right
                            validator:              IntValidator{ bottom: 1; top: 5000; }
                            fact:                   _maxExposure
                            enabled:                controller.parameterExists(90, "MAX_EXPOSURE")

                            Component.onCompleted:  {
                                if (maxExposureText.enabled) {
                                    _maxExposure = controller.getParameterFact(90, "MAX_EXPOSURE");
                                }
                            }
                        }

                        // Offset Settings
                        QGCLabel {
                            id:                     xyzOffsetLabel
                            anchors.margins:        _margins
                            anchors.left:           parent.left
                            anchors.top:            maxExposureText.bottom
                            text:                   qsTr("Spatial Offset (Meters)")
                        }

                        QGCLabel {
                            id:                     xOffsetLabel
                            anchors.margins:        _margins
                            anchors.left:           parent.left
                            anchors.baseline:       xOffsetText.baseline
                            text:                   qsTr("X: ")
                        }

                        FactTextField {
                            id:                     xOffsetText
                            anchors.margins:        _margins
                            anchors.top:            xyzOffsetLabel.bottom
                            anchors.left:           phiOffsetLabel.right
                            fact:                   _xOffset
                            enabled:                controller.parameterExists(90, "CAM_X_OFF")

                            Component.onCompleted:  {
                                if (xOffsetText.enabled) {
                                    _xOffset = controller.getParameterFact(90, "CAM_X_OFF");
                                }
                            }
                        }

                        QGCLabel {
                            id:                     yOffsetLabel
                            anchors.margins:        _margins
                            anchors.left:           xOffsetText.right
                            anchors.baseline:       yOffsetText.baseline
                            text:                   qsTr("Y: ")
                        }

                        FactTextField {
                            id:                     yOffsetText
                            anchors.margins:        _margins
                            anchors.top:            xyzOffsetLabel.bottom
                            anchors.left:           thetaOffsetLabel.right
                            fact:                   _yOffset
                            enabled:                controller.parameterExists(90, "CAM_Y_OFF")

                            Component.onCompleted:  {
                                if (yOffsetText.enabled) {
                                    _yOffset = controller.getParameterFact(90, "CAM_Y_OFF");
                                }
                            }
                        }

                        QGCLabel {
                            id:                     zOffsetLabel
                            anchors.margins:        _margins
                            anchors.left:           yOffsetText.right
                            anchors.baseline:       zOffsetText.baseline
                            text:                   qsTr("Z: ")
                        }

                        FactTextField {
                            id:                     zOffsetText
                            anchors.margins:        _margins
                            anchors.top:            xyzOffsetLabel.bottom
                            anchors.left:           psiOffsetLabel.right
                            fact:                   _zOffset
                            enabled:                controller.parameterExists(90, "CAM_Z_OFF")

                            Component.onCompleted:  {
                                if (zOffsetText.enabled) {
                                    _zOffset = controller.getParameterFact(90, "CAM_Z_OFF");
                                }
                            }
                        }

                        QGCLabel {
                            id:                     angleOffsetLabel
                            anchors.margins:        _margins
                            anchors.left:           parent.left
                            anchors.top:            zOffsetText.bottom
                            text:                   qsTr("Angle Offset (Degrees)")
                        }

                        QGCLabel {
                            id:                     phiOffsetLabel
                            anchors.margins:        _margins
                            anchors.left:           parent.left
                            anchors.baseline:       phiOffsetText.baseline
                            text:                   qsTr("Phi: ")
                        }

                        FactTextField {
                            id:                     phiOffsetText
                            anchors.margins:        _margins
                            anchors.top:            angleOffsetLabel.bottom
                            anchors.left:           phiOffsetLabel.right
                            validator:              DoubleValidator{ bottom: 0.0; top: 359.99; }
                            fact:                   _phiOffset
                            enabled:                controller.parameterExists(90, "CAM_PHI_OFF")

                            Component.onCompleted:  {
                                if (phiOffsetText.enabled) {
                                    _phiOffset = controller.getParameterFact(90, "CAM_PHI_OFF");
                                }
                            }
                        }

                        QGCLabel {
                            id:                     thetaOffsetLabel
                            anchors.margins:        _margins
                            anchors.left:           phiOffsetText.right
                            anchors.baseline:       thetaOffsetText.baseline
                            text:                   qsTr("Theta: ")
                        }

                        FactTextField {
                            id:                     thetaOffsetText
                            anchors.margins:        _margins
                            anchors.top:            angleOffsetLabel.bottom
                            anchors.left:           thetaOffsetLabel.right
                            validator:              DoubleValidator{ bottom: 0.0; top: 359.99; }
                            fact:                   _thetaOffset
                            enabled:                controller.parameterExists(90, "CAM_THETA_OFF")

                            Component.onCompleted:  {
                                if (thetaOffsetText.enabled) {
                                    _thetaOffset = controller.getParameterFact(90, "CAM_THETA_OFF");
                                }
                            }
                        }

                        QGCLabel {
                            id:                     psiOffsetLabel
                            anchors.margins:        _margins
                            anchors.left:           thetaOffsetText.right
                            anchors.baseline:       psiOffsetText.baseline
                            text:                   qsTr("Psi: ")
                        }

                        FactTextField {
                            id:                     psiOffsetText
                            anchors.margins:        _margins
                            anchors.top:            angleOffsetLabel.bottom
                            anchors.left:           psiOffsetLabel.right
                            validator:              DoubleValidator{ bottom: 0.0; top: 359.99; }
                            fact:                   _psiOffset
                            enabled:                controller.parameterExists(90, "CAM_PSI_OFF")

                            Component.onCompleted:  {
                                if (psiOffsetText.enabled) {
                                    _psiOffset = controller.getParameterFact(90, "CAM_PSI_OFF");
                                }
                            }
                        }
                    } // Rectangle
                } // Item
            } // Component - cameraSettings

            // Controller Settings
            Component {
                id: controllerSettings

                Item {
                    width:  rectangle.x + rectangle.width
                    height: rectangle.y + rectangle.height

                    property Fact _trackTagInManual:    Fact{}
                    property Fact _trackTagYaw:         Fact{}
                    property Fact _trackTagCamera:      Fact{}
                    property Fact _maxLeanAngle:        Fact{}

                    QGCLabel {
                        id:         controllerSettingLabel
                        text:       qsTr("Controller")
                        font.family: ScreenTools.demiboldFontFamily
                    }

                    Rectangle {
                        id:                 rectangle
                        anchors.topMargin:  _margins / 2
                        anchors.left:       parent.left
                        anchors.top:        controllerSettingLabel.bottom
                        width:              trackCameraCheckbox.x + trackCameraCheckbox.width + _margins
                        height:             maxLeanAngleText.y + maxLeanAngleText.height + _margins
                        color:              palette.windowShade

                        QGCLabel {
                            id:                     trackTagLabel
                            anchors.margins:        _margins
                            anchors.left:           parent.left
                            anchors.baseline:       trackTagInManualCheckbox.baseline
                            text:                   qsTr("Tag Tracking: ")
                        }

                        FactCheckBox {
                            id:                     trackTagInManualCheckbox
                            anchors.margins:        _margins
                            anchors.top:            parent.top
                            anchors.left:           trackTagLabel.right
                            text:                   qsTr("In Manual Mode")
                            fact:                   _trackTagInManual
                            checkedValue:           1
                            uncheckedValue:         0
                            enabled:                controller.parameterExists(90, "TRACK_TAG_MANUAL")

                            Component.onCompleted: {
                                if (trackTagInManualCheckbox.enabled) {
                                    _trackTagInManual = controller.getParameterFact(90, "TRACK_TAG_MANUAL");
                                }
                            }
                        }

                        FactCheckBox {
                            id:                     trackTagYawCheckbox
                            anchors.margins:        _margins
                            anchors.top:            parent.top
                            anchors.left:           trackTagInManualCheckbox.right
                            text:                   qsTr("Yaw Tracking")
                            fact:                   _trackTagYaw
                            checkedValue:           1
                            uncheckedValue:         0
                            enabled:                controller.parameterExists(90, "TRACK_TAG_YAW")

                            Component.onCompleted: {
                                if (trackTagYawCheckbox.enabled) {
                                    _trackTagYaw = controller.getParameterFact(90, "TRACK_TAG_YAW");
                                }
                            }
                        }

                        FactCheckBox {
                            id:                     trackCameraCheckbox
                            anchors.margins:        _margins
                            anchors.top:            parent.top
                            anchors.left:           trackTagYawCheckbox.right
                            text:                   qsTr("Camera-Centric")
                            fact:                   _trackTagCamera
                            checkedValue:           1
                            uncheckedValue:         0
                            enabled:                controller.parameterExists(90, "TRACK_CAMERA")

                            Component.onCompleted: {
                                if (trackCameraCheckbox.enabled) {
                                    _trackTagCamera = controller.getParameterFact(90, "TRACK_CAMERA");
                                }
                            }
                        }

                        QGCLabel {
                            id:                     maxLeanAngleLabel
                            anchors.margins:        _margins
                            anchors.left:           parent.left
                            anchors.baseline:       maxLeanAngleText.baseline
                            text:                   qsTr("Maximum Lean Angle: ")
                        }

                        FactTextField {
                            id:                     maxLeanAngleText
                            anchors.margins:        _margins
                            anchors.top:            trackTagInManualCheckbox.bottom
                            anchors.left:           maxLeanAngleLabel.right
                            validator:              DoubleValidator{ bottom: 5.0; top: 45.0; }
                            fact:                   _maxLeanAngle
                            enabled:                controller.parameterExists(90, "MAX_LEAN_ANGLE")

                            Component.onCompleted: {
                                if (maxLeanAngleText) {
                                    _maxLeanAngle = controller.getParameterFact(90, "MAX_LEAN_ANGLE");
                                }
                            }
                        }

                        QGCLabel {
                            id:                     maxLeanAngleUnits
                            anchors.margins:        _margins
                            anchors.left:           maxLeanAngleText.right
                            anchors.baseline:       maxLeanAngleText.baseline
                            text:                   qsTr("Degrees (5-45)")
                        }
                    } // Rectangle

                } // Item
            } // Component - controllerSettings

            // commsSettings
            Component {
                id: commsSettings

                Item {
                    width:  rectangle.x + rectangle.width
                    height: rectangle.y + rectangle.height

                    property Fact _streamEnable:        Fact{}
                    property Fact _streamAddr:          Fact{}
                    property Fact _streamPort:          Fact{}
                    property Fact _remotelogAddr:       Fact{}
                    property Fact _remotelogPort:       Fact{}

                    // https://stackoverflow.com/questions/10834796/validate-that-a-string-is-a-positive-integer
                    function isNormalInteger(str) {
                        return /^\+?(0|[1-9]\d*)$/.test(str);
                    }

                    function intToIpv4(value) {
                        return ((value >> 0)  & 0xFF).toString() + "." +
                               ((value >> 8)  & 0xFF).toString() + "." +
                               ((value >> 16) & 0xFF).toString() + "." +
                               ((value >> 24) & 0xFF).toString();
                    }

                    function ipv4ToInt(value)  {
                        var tokens = value.split(".");
                        // IPv4 length validity check
                        if(tokens.length != 4) return -1;
                        var encoded = 0;
                        for (var i = 0; i < tokens.length; ++i) {
                            if(!isNormalInteger(tokens[i])) return -1;
                            var currentByte = Number.parseInt(tokens[i]);
                            // IPv4 byte check
                            if(currentByte < 0 || currentByte > 255) return -1;
                            encoded += (currentByte << (i*8));
                        }
                        return encoded;
                    }

                    function setValue(addrFact, portFact, value) {
                        var tokens = value.split(":");
                        // Ensure address and port configuration is correct
                        if(tokens.length != 2) return;
                        var addr = ipv4ToInt(tokens[0]);
                        if(addr < 0) return;
                        // Port number should be an integer greater than 0
                        if(!isNormalInteger(tokens[1])) return;
                        var port = Number.parseInt(tokens[1]);
                        if(port < 0) return;
                        addrFact.value = addr;
                        portFact.value = port;
                    }

                    QGCLabel {
                        id:         commsSettingLabel
                        text:       qsTr("Comms")
                        font.family: ScreenTools.demiboldFontFamily
                    }

                    Rectangle {
                        id:                 rectangle
                        anchors.topMargin:  _margins / 2
                        anchors.left:       parent.left
                        anchors.top:        commsSettingLabel.bottom
                        width:              streamEnableCheckbox.x + streamEnableCheckbox.width + _margins
                        height:             remotelogAddressText.y + remotelogAddressText.height + _margins
                        color:              palette.windowShade

                        // Stream Settings
                        QGCLabel {
                            id:                     streamLabel
                            anchors.margins:        _margins
                            anchors.left:           parent.left
                            anchors.baseline:       streamAddressText.baseline
                            text:                   qsTr("Video: ")
                        }

                        QGCTextField {
                            id:                     streamAddressText
                            anchors.margins:        _margins
                            anchors.left:           streamLabel.right
                            anchors.top:            parent.top
                            width:                  ScreenTools.defaultFontPixelWidth * 22
                            enabled:                controller.parameterExists(90, "STREAM_IPADDR") &&
                                                    controller.parameterExists(90, "STREAM_PORT")
                            onEditingFinished:      {
                                setValue(_streamAddr, _streamPort, text)
                                streamAddressText.text = intToIpv4(_streamAddr.value) + ":" + _streamPort.value.toString();
                            }

                            Component.onCompleted: {
                                if (streamAddressText.enabled) {
                                    _streamAddr = controller.getParameterFact(90, "STREAM_IPADDR");
                                    _streamPort = controller.getParameterFact(90, "STREAM_PORT");
                                    streamAddressText.text = intToIpv4(_streamAddr.value) + ":" + _streamPort.value.toString();
                                }
                            }
                        }

                        FactCheckBox {
                            id:                     streamEnableCheckbox
                            anchors.margins:        _margins
                            anchors.left:           streamAddressText.right
                            anchors.baseline:       streamAddressText.baseline
                            fact:                   _streamEnable
                            text:                   qsTr("Enable")
                            checkedValue:           1
                            uncheckedValue:         0
                            enabled:                controller.parameterExists(90, "STREAM_ENABLE")

                            Component.onCompleted: {
                                if (streamEnableCheckbox.enabled) {
                                    _streamEnable = controller.getParameterFact(90, "STREAM_ENABLE");
                                }
                            }
                        }

                        // Remote Log Settings
                        QGCLabel {
                            id:                     remotelogLabel
                            anchors.margins:        _margins
                            anchors.left:           parent.left
                            anchors.baseline:       remotelogAddressText.baseline
                            text:                   qsTr("Remote Logging: ")
                        }

                        QGCTextField {
                            id:                     remotelogAddressText
                            anchors.margins:        _margins
                            anchors.left:           remotelogLabel.right
                            anchors.top:            streamAddressText.bottom
                            width:                  ScreenTools.defaultFontPixelWidth * 22
                            enabled:                controller.parameterExists(90, "REMOTE_IPADDR") &&
                                                    controller.parameterExists(90, "REMOTE_PORT")
                            onEditingFinished:      {
                                setValue(_remotelogAddr, _remotelogPort, text)
                                remotelogAddressText.text = intToIpv4(_remotelogAddr.value) + ":" + _remotelogPort.value.toString();
                            }

                            Component.onCompleted: {
                                if (remotelogAddressText.enabled) {
                                    _remotelogAddr = controller.getParameterFact(90, "REMOTE_IPADDR");
                                    _remotelogPort = controller.getParameterFact(90, "REMOTE_PORT");
                                    remotelogAddressText.text = intToIpv4(_remotelogAddr.value) + ":" + _remotelogPort.value.toString();
                                }
                            }
                        }

                    } // Rectangle
                } // Item
            } // Component - commsSettings

            // Component Loaders
            Loader {
                id: tagSettingsLoader
                sourceComponent: tagSettings
            }

            Loader {
                id: cameraSettingsLoader
                sourceComponent: cameraSettings
            }

            Loader {
                id: controllerSettingsLoader
                sourceComponent: controllerSettings
            }

            Loader {
                id: commsSettingsLoader
                sourceComponent: commsSettings
            }
        } // Column
    } // Component
}
