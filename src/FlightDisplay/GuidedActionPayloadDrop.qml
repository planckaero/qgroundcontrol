import QGroundControl.FlightDisplay 1.0

GuidedToolStripAction {
    text:       _guidedController.payloadDropTitle
    iconSource: "/res/payload-drop.svg"
    visible:    _guidedController.showPayloadDrop
    enabled:    _guidedController.showPayloadDrop
    actionID:   _guidedController.actionPayloadDrop
}
