import QGroundControl.Controls 1.0
import QGroundControl.FlightDisplay 1.0

ToolStripAction {
    property int    actionID: _guidedController.actionPayloadDrop
    property string message

    property var _guidedController: globals.guidedControllerFlyView

    text:       _guidedController.payloadDropTitle
    visible:    true
    enabled:    true // _guidedController.showPayloadDrop
    iconSource: "/res/payload-drop.svg"

    onTriggered: {
        _guidedController.dropPayloadRequest()
    }
}
