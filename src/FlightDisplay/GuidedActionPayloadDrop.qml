

import QGroundControl.FlightDisplay 1.0

GuidedToolStripAction {
    text:       _guidedController.
    iconSource: "/res/takeoff.svg"
    visible:    _guidedController.showTakeoff || !_guidedController.showLand
    enabled:    _guidedController.showTakeoff
    actionID:   _guidedController.actionTakeoff
}
