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
import QtLocation       5.3
import QtPositioning    5.3
import QtQuick.Dialogs  1.2

import QGroundControl                       1.0
import QGroundControl.FactSystem            1.0
import QGroundControl.Controls              1.0
import QGroundControl.FlightMap             1.0
import QGroundControl.ScreenTools           1.0
import QGroundControl.MultiVehicleManager   1.0
import QGroundControl.Vehicle               1.0
import QGroundControl.QGCPositionManager    1.0

Map {
    id: _map

    //-- Qt 5.9 has rotation gesture enabled by default. Here we limit the possible gestures.
    gesture.acceptedGestures:   MapGestureArea.PinchGesture | MapGestureArea.PanGesture | MapGestureArea.FlickGesture
    gesture.flickDeceleration:  3000
    plugin:                     Plugin { name: "QGroundControl" }

    // https://bugreports.qt.io/browse/QTBUG-82185
    opacity:                    0.99

    property string mapName:                        'defaultMap'
    property bool   isSatelliteMap:                 activeMapType.name.indexOf("Satellite") > -1 || activeMapType.name.indexOf("Hybrid") > -1
    property var    gcsPosition:                    QGroundControl.qgcPositionManger.gcsPosition
    property real   gcsHeading:                     QGroundControl.qgcPositionManger.gcsHeading
    property bool   userPanned:                     false   ///< true: the user has manually panned the map
    property bool   userPanning:                    false
    property bool   allowGCSLocationCenter:         false   ///< true: map will center/zoom to gcs location one time
    property bool   allowVehicleLocationCenter:     false   ///< true: map will center/zoom to vehicle location one time
    property bool   firstGCSPositionReceived:       false   ///< true: first gcs position update was responded to
    property bool   firstVehiclePositionReceived:   false   ///< true: first vehicle position update was responded to
    property bool   planView:                       false   ///< true: map being using for Plan view, items should be draggable

    readonly property real  maxZoomLevel: 20

    property var    activeVehicleCoordinate:        activeVehicle ? activeVehicle.coordinate : QtPositioning.coordinate()

    function setVisibleRegion(region) {
        // TODO: Is this still necessary with Qt 5.11?
        // This works around a bug on Qt where if you set a visibleRegion and then the user moves or zooms the map
        // and then you set the same visibleRegion the map will not move/scale appropriately since it thinks there
        // is nothing to do.
        _map.visibleRegion = QtPositioning.rectangle(QtPositioning.coordinate(0, 0), QtPositioning.coordinate(0, 0))
        _map.visibleRegion = region
    }

    function _possiblyCenterToVehiclePosition() {
        if (!firstVehiclePositionReceived && allowVehicleLocationCenter && activeVehicleCoordinate.isValid) {
            firstVehiclePositionReceived = true
            center = activeVehicleCoordinate
            zoomLevel = QGroundControl.flightMapInitialZoom
        }
    }

    function centerToSpecifiedLocation() {
        mainWindow.showComponentDialog(specifyMapPositionDialog, qsTr("Specify Position"), mainWindow.showDialogDefaultWidth, StandardButton.Close)
    }

    Component {
        id: specifyMapPositionDialog
        EditPositionDialog {
            coordinate:             center
            onCoordinateChanged:    center = coordinate
        }
    }
/*
    readonly property double meters_to_deg: 0.000008983152841

    // 10m range ring
        MapCircle {
            center: gcsPosition
            radius: 10
            color: "transparent"
            border.color: "lightgreen"
            border.width: 2
        }

        // 10m rectangle
        MapQuickItem {
            id: rect10m
            coordinate {
                latitude: gcsPosition.latitude + (meters_to_deg * 10)
                longitude: gcsPosition.longitude
            }
            sourceItem: Rectangle {
                width: 30
                height: 15
                color: "black"
            }
        }

        // 10m ring label
        MapQuickItem {
            id: label10m
            coordinate {
                latitude: gcsPosition.latitude + (meters_to_deg * 10)
                longitude: gcsPosition.longitude
            }
            sourceItem: Text {
                text: "10m"
                color: "white"
            }
        }

        // 25m range ring
        MapCircle {
            center: gcsPosition
            radius: 25
            color: "transparent"
            border.color: "orange"
            border.width: 2
        }

        // 25m rectangle
        MapQuickItem {
            id: rect25m
            coordinate {
                latitude: gcsPosition.latitude + (meters_to_deg * 25)
                longitude: gcsPosition.longitude
            }

            sourceItem: Rectangle {
                width: 30
                height: 15
                color: "black"
            }
        }

        // 25m ring label
        MapQuickItem {
            id: label25m
            coordinate {
                latitude: gcsPosition.latitude + (meters_to_deg * 25)
                longitude: gcsPosition.longitude
            }

            sourceItem: Text {
                text: "25m"
                color: "white"
            }
        }

        // 50m range ring
            MapCircle {
                center: gcsPosition
                radius: 50
                color: "transparent"
                border.color: "yellow"
                border.width: 2
            }

            // 50m rectangle
            MapQuickItem {
                id: rect50m
                coordinate {
                    latitude: gcsPosition.latitude + (meters_to_deg * 50)
                    longitude: gcsPosition.longitude
                }
                sourceItem: Rectangle {
                    width: 30
                    height: 15
                    color: "black"
                }
            }

            // 50m ring label
            MapQuickItem {
                id: label50m
                coordinate {
                    latitude: gcsPosition.latitude + (meters_to_deg * 50)
                    longitude: gcsPosition.longitude
                }
                sourceItem: Text {
                    text: "50m"
                    color: "white"
                }
            }

            // 100m range ring
            MapCircle {
                center: gcsPosition
                radius: 100
                color: "transparent"
                border.color: "red"
                border.width: 2
            }

            // 100m rectangle
            MapQuickItem {
                id: rect100m
                coordinate {
                    latitude: gcsPosition.latitude + (meters_to_deg * 100)
                    longitude: gcsPosition.longitude
                }
                sourceItem: Rectangle {
                    width: 30
                    height: 15
                    color: "black"
                }
            }

            // 100m ring label
            MapQuickItem {
                id: label100m
                coordinate {
                    latitude: gcsPosition.latitude + (meters_to_deg * 100)
                    longitude: gcsPosition.longitude
                }
                sourceItem: Text {
                    text: "100m"
                    color: "white"
                }
            }

            // 1000m range ring
            MapCircle {
                center: gcsPosition
                radius: 1000
                color: "transparent"
                border.color: "greenyellow"
                border.width: 2
            }

            // 1000m rectangle
            MapQuickItem {
                id: rect1000m
                coordinate {
                    latitude: gcsPosition.latitude + (meters_to_deg * 1000)
                    longitude: gcsPosition.longitude
                }

                sourceItem: Rectangle {
                    width: 30
                    height: 15
                    color: "black"
                }
            }

            // 1000m ring label
            MapQuickItem {
                id: label1000m
                coordinate {
                    latitude: gcsPosition.latitude + (meters_to_deg * 1000)
                    longitude: gcsPosition.longitude
                }

                sourceItem: Text {
                    text: "1km"
                    color: "white"
                }
            }
*/

    // We track whether the user has panned or not to correctly handle automatic map positioning
    Connections {
        target: gesture

        onPanStarted:      userPanning = true
        onPanFinished:     userPanning = false
    }

    function updateActiveMapType() {
        var settings =  QGroundControl.settingsManager.flightMapSettings
        var fullMapName = settings.mapProvider.value + " " + settings.mapType.value

        for (var i = 0; i < _map.supportedMapTypes.length; i++) {
            if (fullMapName === _map.supportedMapTypes[i].name) {
                _map.activeMapType = _map.supportedMapTypes[i]
                return
            }
        }
    }

    onActiveVehicleCoordinateChanged: _possiblyCenterToVehiclePosition()

    Component.onCompleted: {
        updateActiveMapType()
        _possiblyCenterToVehiclePosition()
    }

    Connections {
        target:             QGroundControl.settingsManager.flightMapSettings.mapType
        onRawValueChanged:  updateActiveMapType()
    }

    Connections {
        target:             QGroundControl.settingsManager.flightMapSettings.mapProvider
        onRawValueChanged:  updateActiveMapType()
    }

    /// Ground Station location
    MapQuickItem {
        anchorPoint.x:  sourceItem.width / 2
        anchorPoint.y:  sourceItem.height / 2
        visible:        gcsPosition.isValid
        coordinate:     gcsPosition

        sourceItem: Image {
            source:         "/res/PlanckTag"
            mipmap:         true
            antialiasing:   true
            fillMode:       Image.PreserveAspectFit
            height:         ScreenTools.defaultFontPixelHeight * (isNaN(gcsHeading) ? 1.75 : 2.5 )
            sourceSize.height: height
        }
    }
} // Map
