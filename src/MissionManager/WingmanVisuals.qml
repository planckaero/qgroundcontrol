/****************************************************************************
 *
 *   (c) 2009-2016 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
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

import QGroundControl                   1.0
import QGroundControl.ScreenTools       1.0
import QGroundControl.Palette           1.0
import QGroundControl.Controls          1.0
import QGroundControl.FlightMap         1.0
import QGroundControl.ShapeFileHelper   1.0

/// Wingman map visuals
Item {
    id: _root

    property var    qgcView                     ///< QGCView for popping dialogs
    property var    mapControl                  ///< Map control to place item in
    property var    wingman:        QGroundControl.qgcPositionManger.wingman  ///< Wingman object
    property int    lineWidth:      3
    property color  lineColor:      "#be781c"
    property var    setpoint:       wingman ? wingman.setpoint : new QGeoCoordinate(0)
    property var    gcsLocation:    wingman ? wingman.gcsLocation : new QGeoCoordinate(0)


    property var    _wingmanComponent
    property var    _dragHandlesComponent
    property var    _splitHandlesComponent

    property real _zorderDragHandle:    QGroundControl.zOrderMapItems + 3   // Highest to prevent splitting when items overlap
    property real _zorderSplitHandle:   QGroundControl.zOrderMapItems + 2

    function addVisuals() {
        _wingmanComponent = wingmanComponent.createObject(mapControl)
        mapControl.addMapItem(_wingmanComponent)
    }

    function removeVisuals() {
        _wingmanComponent.destroy()
    }

    function addHandles() {
        if (!_dragHandlesComponent) {
            _dragHandlesComponent = dragHandlesComponent.createObject(mapControl)
            _splitHandlesComponent = splitHandlesComponent.createObject(mapControl)
        }
    }

    function removeHandles() {
        if (_dragHandlesComponent) {
            _dragHandlesComponent.destroy()
            _dragHandlesComponent = undefined
        }
        if (_splitHandlesComponent) {
            _splitHandlesComponent.destroy()
            _splitHandlesComponent = undefined
        }
    }

    /// Calculate the default/initial polyline
    function defaultPolylineVertices() {
        var x = map.centerViewport.x + (map.centerViewport.width / 2)
        var yInset = map.centerViewport.height / 4
        var topPointCoord =     map.toCoordinate(Qt.point(x, map.centerViewport.y + yInset),                                false /* clipToViewPort */)
        var bottomPointCoord =  map.toCoordinate(Qt.point(x, map.centerViewport.y + map.centerViewport.height - yInset),    false /* clipToViewPort */)
        return [ topPointCoord, bottomPointCoord ]
    }

    /// Add an initial 2 point polyline
    function addInitialPolyline() {
        if (wingman.count < 2) {
            wingman.clear()
            var initialVertices = defaultPolylineVertices()
            wingman.appendVertex(initialVertices[0])
            wingman.appendVertex(initialVertices[1])
        }
    }

    /// Reset polyline back to initial default
    function resetPolyline() {
        wingman.clear()
        addInitialPolyline()
    }

    /*onInteractiveChanged: {
        if (interactive) {
            addHandles()
        } else {
            removeHandles()
        }
    }*/

    Component.onCompleted: {
        addVisuals()
        /*if (interactive) {
            addHandles()
        }*/
    }

    Component.onDestruction: {
        removeVisuals()
        removeHandles()
    }

    QGCPalette { id: qgcPal }

    Menu {
        id: menu
        property int _removeVertexIndex

        function popUpWithIndex(curIndex) {
            _removeVertexIndex = curIndex
            removeVertexItem.visible = wingman.count > 2
            menu.popup()
        }

        MenuItem {
            id:             removeVertexItem
            text:           qsTr("Remove vertex" )
            onTriggered:    mapPolyline.removeVertex(menu._removeVertexIndex)
        }

        MenuSeparator {
            visible:        removeVertexItem.visible
        }

        MenuItem {
            text:           qsTr("Edit position..." )
            onTriggered:    qgcView.showDialog(editPositionDialog, qsTr("Edit Position"), qgcView.showDialogDefaultWidth, StandardButton.Cancel)
        }

        MenuItem {
            text:           qsTr("Load KML...")
            onTriggered:    kmlLoadDialog.openForLoad()
        }
    }

    Component {
        id: editPositionDialog

        EditPositionDialog {
            Component.onCompleted: coordinate = wingman.path[menu._removeVertexIndex]
            onCoordinateChanged:  wingman.adjustVertex(menu._removeVertexIndex,coordinate)
        }
    }



    // Control which is used to drag polygon vertices
    Component {
        id: dragAreaComponent

        MissionItemIndicatorDrag {
            mapControl: _root.mapControl
            id:         dragArea
            z:          _zorderDragHandle

            property int polylineVertex

            property bool _creationComplete: false

            Component.onCompleted: _creationComplete = true

            onItemCoordinateChanged: {
                if (_creationComplete) {
                    // During component creation some bad coordinate values got through which screws up draw
                    //wingman.adjustVertex(polylineVertex, itemCoordinate)
                }
            }

            onClicked: {
                menu.popUpWithIndex(polylineVertex)
            }

        }
    }

    Component {
        id: dragHandleComponent

        MapQuickItem {
            id:             mapQuickItem
            anchorPoint.x:  dragHandle.width / 2
            anchorPoint.y:  dragHandle.height / 2
            z:              _zorderDragHandle

            property int polylineVertex

            sourceItem: Rectangle {
                id:             dragHandle
                width:          ScreenTools.defaultFontPixelHeight * 1.5
                height:         width
                radius:         width * 0.5
                color:          Qt.rgba(1,1,1,0.8)
                border.color:   Qt.rgba(0,0,0,0.25)
                border.width:   1
            }
        }
    }

    // Add all polygon vertex drag handles to the map
    Component {
        id: dragHandlesComponent

        Repeater {
            model: wingman.pathModel

            delegate: Item {
                property var _visuals: [ ]

                Component.onCompleted: {
                    var dragHandle = dragHandleComponent.createObject(mapControl)
                    dragHandle.coordinate = Qt.binding(function() { return object.coordinate })
                    dragHandle.polylineVertex = Qt.binding(function() { return index })
                    mapControl.addMapItem(dragHandle)
                    var dragArea = dragAreaComponent.createObject(mapControl, { "itemIndicator": dragHandle, "itemCoordinate": object.coordinate })
                    dragArea.polylineVertex = Qt.binding(function() { return index })
                    _visuals.push(dragHandle)
                    _visuals.push(dragArea)
                }

                Component.onDestruction: {
                    for (var i=0; i<_visuals.length; i++) {
                        _visuals[i].destroy()
                    }
                    _visuals = [ ]
                }
            }
        }
    }



    /// Line from GCS to Wingman setpoint
    Component {
        id: wingmanComponent

        MapPolyline {
            line.width: lineWidth
            line.color: lineColor
            path:       wingman ? wingman.path : 0
        }
    }

    /// Wingman Setpoint Location
    MapQuickItem {
        id:             wingmanSetpointItem
        anchorPoint.x:  sourceItem.width / 2
        anchorPoint.y:  sourceItem.height / 2
        visible:        visible
        coordinate:     setpoint

        sourceItem: Image {
            source:         "/res/clockwise-arrow.svg"
            mipmap:         true
            antialiasing:   true
            fillMode:       Image.PreserveAspectFit
            height:         ScreenTools.defaultFontPixelHeight * (isNaN(gcsHeading) ? 1.75 : 2.5 )
            sourceSize.height: height
            /*transform: Rotation {
                origin.x:       mapItemImage.width  / 2
                origin.y:       mapItemImage.height / 2
                angle:          0 //isNaN(gcsHeading) ? 0 : gcsHeading
            }*/
        }
    }
}

