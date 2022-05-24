import QGroundControl.FlightDisplay 1.0

GuidedToolStripAction {
    text:       _guidedController.ledToggleTitle
    visible:    true
    enabled:    _guidedController.showLedToggle
    iconSource: "/res/LEDOn.svg"
    actionID:   _guidedController.actionLedToggle
}
