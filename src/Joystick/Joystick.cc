/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/


#include "Joystick.h"
#include "QGC.h"
#include "AutoPilotPlugin.h"
#include "UAS.h"
#include "QGCApplication.h"
#include "VideoManager.h"
#include "QGCCameraManager.h"
#include "QGCCameraControl.h"

#include <QSettings>

QGC_LOGGING_CATEGORY(JoystickLog,       "JoystickLog")
QGC_LOGGING_CATEGORY(JoystickValuesLog, "JoystickValuesLog")

const char* Joystick::_settingsGroup =                  "Joysticks";
const char* Joystick::_calibratedSettingsKey =          "Calibrated4"; // Increment number to force recalibration
const char* Joystick::_buttonActionNameKey =            "ButtonActionName%1";
const char* Joystick::_buttonActionRepeatKey =          "ButtonActionRepeat%1";
const char* Joystick::_throttleModeSettingsKey =        "ThrottleMode";
const char* Joystick::_exponentialSettingsKey =         "Exponential";
const char* Joystick::_accumulatorSettingsKey =         "Accumulator";
const char* Joystick::_deadbandSettingsKey =            "Deadband";
const char* Joystick::_circleCorrectionSettingsKey =    "Circle_Correction";
const char* Joystick::_axisFrequencySettingsKey =       "AxisFrequency";
const char* Joystick::_buttonFrequencySettingsKey =     "ButtonFrequency";
const char* Joystick::_txModeSettingsKey =              nullptr;
const char* Joystick::_fixedWingTXModeSettingsKey =     "TXMode_FixedWing";
const char* Joystick::_multiRotorTXModeSettingsKey =    "TXMode_MultiRotor";
const char* Joystick::_roverTXModeSettingsKey =         "TXMode_Rover";
const char* Joystick::_vtolTXModeSettingsKey =          "TXMode_VTOL";
const char* Joystick::_submarineTXModeSettingsKey =     "TXMode_Submarine";
const char* Joystick::_gimbalSettingsKey =              "GimbalEnabled";
const char* Joystick::_zAxisRC8SettingsKey =            "useZAxisRC8";

const char* Joystick::_buttonActionNone =               QT_TR_NOOP("No Action");
const char* Joystick::_buttonActionArm =                QT_TR_NOOP("Arm");
const char* Joystick::_buttonActionDisarm =             QT_TR_NOOP("Disarm");
const char* Joystick::_buttonActionToggleArm =          QT_TR_NOOP("Toggle Arm");
const char* Joystick::_buttonActionVTOLFixedWing =      QT_TR_NOOP("VTOL: Fixed Wing");
const char* Joystick::_buttonActionVTOLMultiRotor =     QT_TR_NOOP("VTOL: Multi-Rotor");
const char* Joystick::_buttonActionContinuousZoomIn =   QT_TR_NOOP("Continuous Zoom In");
const char* Joystick::_buttonActionContinuousZoomOut =  QT_TR_NOOP("Continuous Zoom Out");
const char* Joystick::_buttonActionStepZoomIn =         QT_TR_NOOP("Step Zoom In");
const char* Joystick::_buttonActionStepZoomOut =        QT_TR_NOOP("Step Zoom Out");
const char* Joystick::_buttonActionNextStream =         QT_TR_NOOP("Next Video Stream");
const char* Joystick::_buttonActionPreviousStream =     QT_TR_NOOP("Previous Video Stream");
const char* Joystick::_buttonActionNextCamera =         QT_TR_NOOP("Next Camera");
const char* Joystick::_buttonActionPreviousCamera =     QT_TR_NOOP("Previous Camera");
const char* Joystick::_buttonActionTriggerCamera =      QT_TR_NOOP("Trigger Camera");
const char* Joystick::_buttonActionStartVideoRecord =   QT_TR_NOOP("Start Recording Video");
const char* Joystick::_buttonActionStopVideoRecord =    QT_TR_NOOP("Stop Recording Video");
const char* Joystick::_buttonActionToggleVideoRecord =  QT_TR_NOOP("Toggle Recording Video");
const char* Joystick::_buttonActionGimbalDown =         QT_TR_NOOP("Gimbal Down");
const char* Joystick::_buttonActionGimbalUp =           QT_TR_NOOP("Gimbal Up");
const char* Joystick::_buttonActionGimbalLeft =         QT_TR_NOOP("Gimbal Left");
const char* Joystick::_buttonActionGimbalRight =        QT_TR_NOOP("Gimbal Right");
const char* Joystick::_buttonActionGimbalCenter =       QT_TR_NOOP("Gimbal Center");

const char* Joystick::_buttonActionGimbalDownRC6 =      QT_TR_NOOP("Gimbal Down (RC6)");
const char* Joystick::_buttonActionGimbalUpRC6 =        QT_TR_NOOP("Gimbal Up (RC6)");
const char* Joystick::_buttonActionGimbalLeftRC7 =      QT_TR_NOOP("Gimbal Left (RC7)");
const char* Joystick::_buttonActionGimbalRightRC7 =     QT_TR_NOOP("Gimbal Right (RC7)");
const char* Joystick::_buttonActionRC9TriState =        QT_TR_NOOP("RC9 Tri-State");
const char* Joystick::_buttonActionRC10TriState =       QT_TR_NOOP("RC10 Tri-State");
const char* Joystick::_buttonActionRC11 =               QT_TR_NOOP("RC11");
const char* Joystick::_buttonActionRC12 =               QT_TR_NOOP("RC12");
const char* Joystick::_buttonActionRC13 =               QT_TR_NOOP("RC13");
const char* Joystick::_buttonActionRC14 =               QT_TR_NOOP("RC14");
const char* Joystick::_buttonActionRC15 =               QT_TR_NOOP("RC15");
const char* Joystick::_buttonActionRC16 =               QT_TR_NOOP("RC16");
const char* Joystick::_buttonActionRC17 =               QT_TR_NOOP("RC17");
const char* Joystick::_buttonActionRC18 =               QT_TR_NOOP("RC18");
const char* Joystick::_buttonActionTriButtonKill =      QT_TR_NOOP("Triple Button E-Stop");
const char* Joystick::_buttonActionPlanckTrackAltHoldToggle = QT_TR_NOOP("Toggle PlanckTrack/AltHold");
const char* Joystick::_buttonActionPlanckTrackLoiterToggle  = QT_TR_NOOP("Toggle PlanckTrack/Loiter");

const char* Joystick::_rgFunctionSettingsKey[Joystick::maxFunction] = {
    "RollAxis",
    "PitchAxis",
    "YawAxis",
    "ThrottleAxis",
    "GimbalPitchAxis",
    "GimbalYawAxis"
};

int Joystick::_transmitterMode = 2;

AssignedButtonAction::AssignedButtonAction(QObject* parent, const QString name)
    : QObject(parent)
    , action(name)
{
}

AssignableButtonAction::AssignableButtonAction(QObject* parent, QString action_, bool canRepeat_)
    : QObject(parent)
    , _action(action_)
    , _repeat(canRepeat_)
{
}

Joystick::Joystick(const QString& name, int axisCount, int buttonCount, int hatCount, MultiVehicleManager* multiVehicleManager)
    : _name(name)
    , _axisCount(axisCount)
    , _buttonCount(buttonCount)
    , _hatCount(hatCount)
    , _hatButtonCount(4 * hatCount)
    , _totalButtonCount(_buttonCount+_hatButtonCount)
    , _multiVehicleManager(multiVehicleManager)
{
    _rgAxisValues   = new int[static_cast<size_t>(_axisCount)];
    _rgCalibration  = new Calibration_t[static_cast<size_t>(_axisCount)];
    _rgButtonValues = new uint8_t[static_cast<size_t>(_totalButtonCount)];
    for (int i = 0; i < _axisCount; i++) {
        _rgAxisValues[i] = 0;
    }
    for (int i = 0; i < _totalButtonCount; i++) {
        _rgButtonValues[i] = BUTTON_UP;
        _buttonActionArray.append(nullptr);
    }
    _buildActionList(_multiVehicleManager->activeVehicle());
    _updateTXModeSettingsKey(_multiVehicleManager->activeVehicle());
    _loadSettings();
    connect(_multiVehicleManager, &MultiVehicleManager::activeVehicleChanged, this, &Joystick::_activeVehicleChanged);
}

Joystick::~Joystick()
{
    // Crash out of the thread if it is still running
    terminate();
    wait();
    delete[] _rgAxisValues;
    delete[] _rgCalibration;
    delete[] _rgButtonValues;
    _assignableButtonActions.clearAndDeleteContents();
    for (int button = 0; button < _totalButtonCount; button++) {
        if(_buttonActionArray[button]) {
            _buttonActionArray[button]->deleteLater();
        }
    }
}

void Joystick::_setDefaultCalibration(void) {
    QSettings settings;
    settings.beginGroup(_settingsGroup);
    settings.beginGroup(_name);
    _calibrated = settings.value(_calibratedSettingsKey, false).toBool();

    // Only set default calibrations if we do not have a calibration for this gamecontroller
    if(_calibrated) return;

    for(int axis = 0; axis < _axisCount; axis++) {
        Joystick::Calibration_t calibration;
        _rgCalibration[axis] = calibration;
    }

    _rgCalibration[1].reversed = true;
    _rgCalibration[3].reversed = true;

    // Default TX Mode 2 axis assignments for gamecontrollers
    _rgFunctionAxis[rollFunction]       = 2;
    _rgFunctionAxis[pitchFunction]      = 3;
    _rgFunctionAxis[yawFunction]        = 0;
    _rgFunctionAxis[throttleFunction]   = 1;

    _rgFunctionAxis[gimbalPitchFunction]= 4;
    _rgFunctionAxis[gimbalYawFunction]  = 5;

    _exponential    = 0;
    _accumulator    = false;
    _deadband       = false;
    _axisFrequency  = 25.0f;
    _buttonFrequency= 5.0f;
    _throttleMode   = ThrottleModeDownZero;
    _calibrated     = true;
    _circleCorrection = false;

    _saveSettings();
}

void Joystick::_updateTXModeSettingsKey(Vehicle* activeVehicle)
{
    if(activeVehicle) {
        if(activeVehicle->fixedWing()) {
            _txModeSettingsKey = _fixedWingTXModeSettingsKey;
        } else if(activeVehicle->multiRotor()) {
            _txModeSettingsKey = _multiRotorTXModeSettingsKey;
        } else if(activeVehicle->rover()) {
            _txModeSettingsKey = _roverTXModeSettingsKey;
        } else if(activeVehicle->vtol()) {
            _txModeSettingsKey = _vtolTXModeSettingsKey;
        } else if(activeVehicle->sub()) {
            _txModeSettingsKey = _submarineTXModeSettingsKey;
        } else {
            _txModeSettingsKey = nullptr;
            qWarning() << "No valid joystick TXmode settings key for selected vehicle";
            return;
        }
    } else {
        _txModeSettingsKey = nullptr;
    }
}

void Joystick::_activeVehicleChanged(Vehicle* activeVehicle)
{
    _updateTXModeSettingsKey(activeVehicle);
    if(activeVehicle) {
        QSettings settings;
        settings.beginGroup(_settingsGroup);
        int mode = settings.value(_txModeSettingsKey, activeVehicle->firmwarePlugin()->defaultJoystickTXMode()).toInt();
        setTXMode(mode);
    }
}

void Joystick::_loadSettings()
{
    QSettings settings;
    settings.beginGroup(_settingsGroup);
    Vehicle* activeVehicle = _multiVehicleManager->activeVehicle();

    if(_txModeSettingsKey && activeVehicle)
        _transmitterMode = settings.value(_txModeSettingsKey, activeVehicle->firmwarePlugin()->defaultJoystickTXMode()).toInt();

    settings.beginGroup(_name);

    bool badSettings = false;
    bool convertOk;

    qCDebug(JoystickLog) << "_loadSettings " << _name;

    _calibrated     = settings.value(_calibratedSettingsKey, false).toBool();
    _exponential    = settings.value(_exponentialSettingsKey, 0).toFloat();
    _accumulator    = settings.value(_accumulatorSettingsKey, false).toBool();
    _deadband       = settings.value(_deadbandSettingsKey, false).toBool();
    _axisFrequency  = settings.value(_axisFrequencySettingsKey, 25.0f).toFloat();
    _buttonFrequency= settings.value(_buttonFrequencySettingsKey, 5.0f).toFloat();
    _circleCorrection = settings.value(_circleCorrectionSettingsKey, false).toBool();
    _gimbalEnabled  = settings.value(_gimbalSettingsKey, false).toBool();
    _useZAxisRC8    = settings.value(_zAxisRC8SettingsKey, false).toBool();

    _throttleMode   = static_cast<ThrottleMode_t>(settings.value(_throttleModeSettingsKey, ThrottleModeDownZero).toInt(&convertOk));
    badSettings |= !convertOk;

    qCDebug(JoystickLog) << "_loadSettings calibrated:txmode:throttlemode:exponential:deadband:badsettings" << _calibrated << _transmitterMode << _throttleMode << _exponential << _deadband << badSettings;

    QString minTpl      ("Axis%1Min");
    QString maxTpl      ("Axis%1Max");
    QString trimTpl     ("Axis%1Trim");
    QString revTpl      ("Axis%1Rev");
    QString deadbndTpl  ("Axis%1Deadbnd");

    for (int axis = 0; axis < _axisCount; axis++) {
        Calibration_t* calibration = &_rgCalibration[axis];

        calibration->center = settings.value(trimTpl.arg(axis), 0).toInt(&convertOk);
        badSettings |= !convertOk;

        calibration->min = settings.value(minTpl.arg(axis), -32768).toInt(&convertOk);
        badSettings |= !convertOk;

        calibration->max = settings.value(maxTpl.arg(axis), 32767).toInt(&convertOk);
        badSettings |= !convertOk;

        calibration->deadband = settings.value(deadbndTpl.arg(axis), 0).toInt(&convertOk);
        badSettings |= !convertOk;

        calibration->reversed = settings.value(revTpl.arg(axis), false).toBool();

        qCDebug(JoystickLog) << "_loadSettings axis:min:max:trim:reversed:deadband:badsettings" << axis << calibration->min << calibration->max << calibration->center << calibration->reversed << calibration->deadband << badSettings;
    }

    int workingAxis = 0;
    for (int function = 0; function < maxFunction; function++) {
        int functionAxis;
        functionAxis = settings.value(_rgFunctionSettingsKey[function], -1).toInt(&convertOk);
        badSettings |= !convertOk || (functionAxis >= _axisCount);
        if(functionAxis >= 0) {
            workingAxis++;
        }
        if(functionAxis < _axisCount) {
            _rgFunctionAxis[function] = functionAxis;
        }
        qCDebug(JoystickLog) << "_loadSettings function:axis:badsettings" << function << functionAxis << badSettings;
    }
    badSettings |= workingAxis < 4;

    // FunctionAxis mappings are always stored in TX mode 2
    // Remap to stored TX mode in settings
    _remapAxes(2, _transmitterMode, _rgFunctionAxis);

    for (int button = 0; button < _totalButtonCount; button++) {
        QString a = settings.value(QString(_buttonActionNameKey).arg(button), QString()).toString();
        if(!a.isEmpty() && a != _buttonActionNone) {
            if(_buttonActionArray[button]) {
                _buttonActionArray[button]->deleteLater();
            }
            AssignedButtonAction* ap = new AssignedButtonAction(this, a);
            ap->repeat = settings.value(QString(_buttonActionRepeatKey).arg(button), false).toBool();
            _buttonActionArray[button] = ap;
            _buttonActionArray[button]->buttonTime.start();
            qCDebug(JoystickLog) << "_loadSettings button:action" << button << _buttonActionArray[button]->action << _buttonActionArray[button]->repeat;
            _initRCOverrideChannels(a, true);
        }
    }

    if (badSettings) {
        _calibrated = false;
        settings.setValue(_calibratedSettingsKey, false);
    }
}

void Joystick::_saveButtonSettings()
{
    QSettings settings;
    settings.beginGroup(_settingsGroup);
    settings.beginGroup(_name);
    for (int button = 0; button < _totalButtonCount; button++) {
        if(_buttonActionArray[button]) {
            settings.setValue(QString(_buttonActionNameKey).arg(button),        _buttonActionArray[button]->action);
            settings.setValue(QString(_buttonActionRepeatKey).arg(button),      _buttonActionArray[button]->repeat);
            qCDebug(JoystickLog) << "_saveButtonSettings button:action" << button <<  _buttonActionArray[button]->action << _buttonActionArray[button]->repeat;
        }
    }
}

void Joystick::_saveSettings()
{
    QSettings settings;
    settings.beginGroup(_settingsGroup);

    // Transmitter mode is static
    // Save the mode we are using
    if(_txModeSettingsKey)
        settings.setValue(_txModeSettingsKey,       _transmitterMode);

    settings.beginGroup(_name);
    settings.setValue(_calibratedSettingsKey,       _calibrated);
    settings.setValue(_exponentialSettingsKey,      _exponential);
    settings.setValue(_accumulatorSettingsKey,      _accumulator);
    settings.setValue(_deadbandSettingsKey,         _deadband);
    settings.setValue(_axisFrequencySettingsKey,    _axisFrequency);
    settings.setValue(_buttonFrequencySettingsKey,  _buttonFrequency);
    settings.setValue(_throttleModeSettingsKey,     _throttleMode);
    settings.setValue(_gimbalSettingsKey,           _gimbalEnabled);
    settings.setValue(_circleCorrectionSettingsKey, _circleCorrection);
    settings.setValue(_zAxisRC8SettingsKey,         _useZAxisRC8);

    qCDebug(JoystickLog) << "_saveSettings calibrated:throttlemode:deadband:txmode" << _calibrated << _throttleMode << _deadband << _circleCorrection << _transmitterMode;

    QString minTpl      ("Axis%1Min");
    QString maxTpl      ("Axis%1Max");
    QString trimTpl     ("Axis%1Trim");
    QString revTpl      ("Axis%1Rev");
    QString deadbndTpl  ("Axis%1Deadbnd");

    for (int axis = 0; axis < _axisCount; axis++) {
        Calibration_t* calibration = &_rgCalibration[axis];
        settings.setValue(trimTpl.arg(axis), calibration->center);
        settings.setValue(minTpl.arg(axis), calibration->min);
        settings.setValue(maxTpl.arg(axis), calibration->max);
        settings.setValue(revTpl.arg(axis), calibration->reversed);
        settings.setValue(deadbndTpl.arg(axis), calibration->deadband);
        qCDebug(JoystickLog) << "_saveSettings name:axis:min:max:trim:reversed:deadband"
                                << _name
                                << axis
                                << calibration->min
                                << calibration->max
                                << calibration->center
                                << calibration->reversed
                                << calibration->deadband;
    }

    // Always save function Axis mappings in TX Mode 2
    // Write mode 2 mappings without changing mapping currently in use
    int temp[maxFunction];
    _remapAxes(_transmitterMode, 2, temp);
    for (int function = 0; function < maxFunction; function++) {
        settings.setValue(_rgFunctionSettingsKey[function], temp[function]);
        qCDebug(JoystickLog) << "_saveSettings name:function:axis" << _name << function << _rgFunctionSettingsKey[function];
    }
    _saveButtonSettings();
}

// Relative mappings of axis functions between different TX modes
int Joystick::_mapFunctionMode(int mode, int function) {
    static const int mapping[][6] = {
        { yawFunction, pitchFunction, rollFunction, throttleFunction, gimbalPitchFunction, gimbalYawFunction },
        { yawFunction, throttleFunction, rollFunction, pitchFunction, gimbalPitchFunction, gimbalYawFunction },
        { rollFunction, pitchFunction, yawFunction, throttleFunction, gimbalPitchFunction, gimbalYawFunction },
        { rollFunction, throttleFunction, yawFunction, pitchFunction, gimbalPitchFunction, gimbalYawFunction }};
    return mapping[mode-1][function];
}

// Remap current axis functions from current TX mode to new TX mode
void Joystick::_remapAxes(int currentMode, int newMode, int (&newMapping)[maxFunction]) {
    int temp[maxFunction];
    for(int function = 0; function < maxFunction; function++) {
        temp[_mapFunctionMode(newMode, function)] = _rgFunctionAxis[_mapFunctionMode(currentMode, function)];
    }
    for(int function = 0; function < maxFunction; function++) {
        newMapping[function] = temp[function];
    }
}

void Joystick::setTXMode(int mode) {
    if(mode > 0 && mode <= 4) {
        _remapAxes(_transmitterMode, mode, _rgFunctionAxis);
        _transmitterMode = mode;
        _saveSettings();
    } else {
        qCWarning(JoystickLog) << "Invalid mode:" << mode;
    }
}

/// Adjust the raw axis value to the -1:1 range given calibration information
float Joystick::_adjustRange(int value, Calibration_t calibration, bool withDeadbands)
{
    float valueNormalized;
    float axisLength;
    float axisBasis;

    if (value > calibration.center) {
        axisBasis = 1.0f;
        valueNormalized = value - calibration.center;
        axisLength =  calibration.max - calibration.center;
    } else {
        axisBasis = -1.0f;
        valueNormalized = calibration.center - value;
        axisLength =  calibration.center - calibration.min;
    }

    float axisPercent;

    if (withDeadbands) {
        if (valueNormalized>calibration.deadband) {
            axisPercent = (valueNormalized - calibration.deadband) / (axisLength - calibration.deadband);
        } else if (valueNormalized<-calibration.deadband) {
            axisPercent = (valueNormalized + calibration.deadband) / (axisLength - calibration.deadband);
        } else {
            axisPercent = 0.f;
        }
    }
    else {
        axisPercent = valueNormalized / axisLength;
    }

    float correctedValue = axisBasis * axisPercent;

    if (calibration.reversed) {
        correctedValue *= -1.0f;
    }

#if 0
    qCDebug(JoystickLog) << "_adjustRange corrected:value:min:max:center:reversed:deadband:basis:normalized:length"
                            << correctedValue
                            << value
                            << calibration.min
                            << calibration.max
                            << calibration.center
                            << calibration.reversed
                            << calibration.deadband
                            << axisBasis
                            << valueNormalized
                            << axisLength;
#endif

    return std::max(-1.0f, std::min(correctedValue, 1.0f));
}


void Joystick::run()
{
    //-- Joystick thread
    _open();
    //-- Reset timers
    _axisTime.start();
    _rcOverrideTime.start();
    for (int buttonIndex = 0; buttonIndex < _totalButtonCount; buttonIndex++) {
        if(_buttonActionArray[buttonIndex]) {
            _buttonActionArray[buttonIndex]->buttonTime.start();
        }
    }
    while (!_exitThread) {
        _update();
        _handleButtons();
        _handleAxis();
        _sendRCOverrides();
        QGC::SLEEP::msleep(20);
    }
    _close();
}

void Joystick::_sendRCOverrides() {
    //Don't send any override messages if there are no channels to send
    for(auto c : _rcOverrideChannels) {
        if(c != UINT16_MAX) {
            int rcOverrideDelay = static_cast<int>(1000.0f / _axisFrequency);
            //-- Check elapsed time since last run
            if(_rcOverrideTime.elapsed() > rcOverrideDelay) {
                _rcOverrideTime.start();
                emit rcOverride(_rcOverrideChannels);
            }
            break; //Break out of the for loop
        }
    }
}

void Joystick::_handleButtons()
{
    int lastBbuttonValues[256];
    //-- Update button states
    for (int buttonIndex = 0; buttonIndex < _buttonCount; buttonIndex++) {
        bool newButtonValue = _getButton(buttonIndex);
        if(buttonIndex < 256)
            lastBbuttonValues[buttonIndex] = _rgButtonValues[buttonIndex];
        if (newButtonValue && _rgButtonValues[buttonIndex] == BUTTON_UP) {
            _rgButtonValues[buttonIndex] = BUTTON_DOWN;
            emit rawButtonPressedChanged(buttonIndex, newButtonValue);
        } else if (!newButtonValue && _rgButtonValues[buttonIndex] != BUTTON_UP) {
            _rgButtonValues[buttonIndex] = BUTTON_UP;
            emit rawButtonPressedChanged(buttonIndex, newButtonValue);
        }
    }
    //-- Update hat - append hat buttons to the end of the normal button list
    int numHatButtons = 4;
    for (int hatIndex = 0; hatIndex < _hatCount; hatIndex++) {
        for (int hatButtonIndex = 0; hatButtonIndex<numHatButtons; hatButtonIndex++) {
            // Create new index value that includes the normal button list
            int rgButtonValueIndex = hatIndex*numHatButtons + hatButtonIndex + _buttonCount;
            // Get hat value from joystick
            bool newButtonValue = _getHat(hatIndex, hatButtonIndex);
            if (newButtonValue && _rgButtonValues[rgButtonValueIndex] == BUTTON_UP) {
                _rgButtonValues[rgButtonValueIndex] = BUTTON_DOWN;
                emit rawButtonPressedChanged(rgButtonValueIndex, newButtonValue);
            } else if (!newButtonValue && _rgButtonValues[rgButtonValueIndex] != BUTTON_UP) {
                _rgButtonValues[rgButtonValueIndex] = BUTTON_UP;
                emit rawButtonPressedChanged(rgButtonValueIndex, newButtonValue);
            }
        }
    }
    //-- Process button press/release
    for (int buttonIndex = 0; buttonIndex < _totalButtonCount; buttonIndex++) {
        if(_rgButtonValues[buttonIndex] == BUTTON_DOWN || _rgButtonValues[buttonIndex] == BUTTON_REPEAT) {
            if(_buttonActionArray[buttonIndex]) {
                QString buttonAction = _buttonActionArray[buttonIndex]->action;
                if(buttonAction.isEmpty() || buttonAction == _buttonActionNone)
                    continue;
                //-- Process single button
                if(!_buttonActionArray[buttonIndex]->repeat) {
                    //-- This button just went down
                    if(_rgButtonValues[buttonIndex] == BUTTON_DOWN) {
                        qCDebug(JoystickLog) << "Single button triggered" << buttonIndex << buttonAction;
                        _executeButtonAction(buttonAction, true);
                    }
                } else {
                    //-- Process repeat buttons
                    int buttonDelay = static_cast<int>(1000.0f / _buttonFrequency);
                    if(_buttonActionArray[buttonIndex]->buttonTime.elapsed() > buttonDelay) {
                        _buttonActionArray[buttonIndex]->buttonTime.start();
                        qCDebug(JoystickLog) << "Repeat button triggered" << buttonIndex << buttonAction;
                        _executeButtonAction(buttonAction, true);
                    }
                }
            }
            //-- Flag it as processed
            _rgButtonValues[buttonIndex] = BUTTON_REPEAT;
        } else if(_rgButtonValues[buttonIndex] == BUTTON_UP) {
            //-- Button up transition
            if(buttonIndex < 256) {
                if(lastBbuttonValues[buttonIndex] == BUTTON_DOWN || lastBbuttonValues[buttonIndex] == BUTTON_REPEAT) {
                    if(_buttonActionArray[buttonIndex]) {
                        QString buttonAction = _buttonActionArray[buttonIndex]->action;
                        if(buttonAction.isEmpty() || buttonAction == _buttonActionNone)
                            continue;
                        qCDebug(JoystickLog) << "Button up" << buttonIndex << buttonAction;
                        _executeButtonAction(buttonAction, false);
                    }
                }
            }
        }
    }
}

void Joystick::_handleAxis()
{
    //-- Get frequency
    int axisDelay = static_cast<int>(1000.0f / _axisFrequency);
    //-- Check elapsed time since last run
    if(_axisTime.elapsed() > axisDelay) {
        _axisTime.start();
        //-- Update axis
        for (int axisIndex = 0; axisIndex < _axisCount; axisIndex++) {
            int newAxisValue = _getAxis(axisIndex);
            // Calibration code requires signal to be emitted even if value hasn't changed
            _rgAxisValues[axisIndex] = newAxisValue;
            emit rawAxisValueChanged(axisIndex, newAxisValue);
        }

        if (_activeVehicle->joystickEnabled() && !_calibrationMode && _calibrated) {
            int     axis = _rgFunctionAxis[rollFunction];
            float   roll = _adjustRange(_rgAxisValues[axis],    _rgCalibration[axis], _deadband);

                    axis = _rgFunctionAxis[pitchFunction];
            float   pitch = _adjustRange(_rgAxisValues[axis],   _rgCalibration[axis], _deadband);

                    axis = _rgFunctionAxis[yawFunction];
            float   yaw = _adjustRange(_rgAxisValues[axis],     _rgCalibration[axis],_deadband);

                    axis = _rgFunctionAxis[throttleFunction];
            float   throttle = _adjustRange(_rgAxisValues[axis],_rgCalibration[axis], _throttleMode==ThrottleModeDownZero?false:_deadband);

            float   gimbalPitch = 0.0f;
            float   gimbalYaw   = 0.0f;

            if(_axisCount > 4) {
                axis = _rgFunctionAxis[gimbalPitchFunction];
                gimbalPitch = _adjustRange(_rgAxisValues[axis], _rgCalibration[axis],_deadband);
            }

            if(_axisCount > 5) {
                axis = _rgFunctionAxis[gimbalYawFunction];
                gimbalYaw = _adjustRange(_rgAxisValues[axis],   _rgCalibration[axis],_deadband);
            }

            //Push the gimbal pitch/yaw into a single value for channel 8
            if(_useZAxisRC8) {
                if(gimbalPitch > 0) {
                    _rcMomentary(_rcOverrideChannels[7], true, true, true);
                } else if (gimbalYaw > 0) {
                    _rcMomentary(_rcOverrideChannels[7], true, true, false);
                } else {
                    _rcMomentary(_rcOverrideChannels[7], false, true, false);
                }
            } else {
                _rcOverrideChannels[7] = UINT16_MAX;
            }

            if (_accumulator) {
                static float throttle_accu = 0.f;
                throttle_accu += throttle * (40 / 1000.f); //for throttle to change from min to max it will take 1000ms (40ms is a loop time)
                throttle_accu = std::max(static_cast<float>(-1.f), std::min(throttle_accu, static_cast<float>(1.f)));
                throttle = throttle_accu;
            }

            if (_circleCorrection) {
                float roll_limited      = std::max(static_cast<float>(-M_PI_4), std::min(roll,      static_cast<float>(M_PI_4)));
                float pitch_limited     = std::max(static_cast<float>(-M_PI_4), std::min(pitch,     static_cast<float>(M_PI_4)));
                float yaw_limited       = std::max(static_cast<float>(-M_PI_4), std::min(yaw,       static_cast<float>(M_PI_4)));
                float throttle_limited  = std::max(static_cast<float>(-M_PI_4), std::min(throttle,  static_cast<float>(M_PI_4)));

                // Map from unit circle to linear range and limit
                roll =      std::max(-1.0f, std::min(tanf(asinf(roll_limited)),     1.0f));
                pitch =     std::max(-1.0f, std::min(tanf(asinf(pitch_limited)),    1.0f));
                yaw =       std::max(-1.0f, std::min(tanf(asinf(yaw_limited)),      1.0f));
                throttle =  std::max(-1.0f, std::min(tanf(asinf(throttle_limited)), 1.0f));
            }

            if ( _exponential < -0.01f) {
                // Exponential (0% to -50% range like most RC radios)
                // _exponential is set by a slider in joystickConfigAdvanced.qml
                // Calculate new RPY with exponential applied
                roll =      -_exponential*powf(roll, 3) + (1+_exponential)*roll;
                pitch =     -_exponential*powf(pitch,3) + (1+_exponential)*pitch;
                yaw =       -_exponential*powf(yaw,  3) + (1+_exponential)*yaw;
            }

            // Adjust throttle to 0:1 range
            if (_throttleMode == ThrottleModeCenterZero && _activeVehicle->supportsThrottleModeCenterZero()) {
                if (!_activeVehicle->supportsNegativeThrust() || !_negativeThrust) {
                    throttle = std::max(0.0f, throttle);
                }
            } else {
                throttle = (throttle + 1.0f) / 2.0f;
            }
            qCDebug(JoystickValuesLog) << "name:roll:pitch:yaw:throttle:gimbalPitch:gimbalYaw" << name() << roll << -pitch << yaw << throttle << gimbalPitch << gimbalYaw;
            // NOTE: The buttonPressedBits going to MANUAL_CONTROL are currently used by ArduSub (and it only handles 16 bits)
            // Set up button bitmap
            quint64 buttonPressedBits = 0;  // Buttons pressed for manualControl signal
            for (int buttonIndex = 0; buttonIndex < _totalButtonCount; buttonIndex++) {
                quint64 buttonBit = static_cast<quint64>(1LL << buttonIndex);
                if (_rgButtonValues[buttonIndex] != BUTTON_UP) {
                    // Mark the button as pressed as long as its pressed
                    buttonPressedBits |= buttonBit;
                }
            }
            uint16_t shortButtons = static_cast<uint16_t>(buttonPressedBits & 0xFFFF);
            emit manualControl(roll, -pitch, yaw, throttle, shortButtons, _activeVehicle->joystickMode());
            if(_activeVehicle && _axisCount > 4 && _gimbalEnabled) {
                //-- TODO: There is nothing consuming this as there are no messages to handle gimbal
                //   the way MANUAL_CONTROL handles the other channels.
                emit manualControlGimbal((gimbalPitch + 1.0f) / 2.0f * 90.0f, gimbalYaw * 180.0f);
            }
        }
    }
}

void Joystick::startPolling(Vehicle* vehicle)
{
    if (vehicle) {
        // If a vehicle is connected, disconnect it
        if (_activeVehicle) {
            UAS* uas = _activeVehicle->uas();
            disconnect(this, &Joystick::manualControl, uas, &UAS::setExternalControlSetpoint);
            disconnect(this, &Joystick::setArmed,           _activeVehicle, &Vehicle::setArmed);
            disconnect(this, &Joystick::setVtolInFwdFlight, _activeVehicle, &Vehicle::setVtolInFwdFlight);
            disconnect(this, &Joystick::setFlightMode,      _activeVehicle, &Vehicle::setFlightMode);
            disconnect(this, &Joystick::gimbalPitchStep,    _activeVehicle, &Vehicle::gimbalPitchStep);
            disconnect(this, &Joystick::gimbalYawStep,      _activeVehicle, &Vehicle::gimbalYawStep);
            disconnect(this, &Joystick::centerGimbal,       _activeVehicle, &Vehicle::centerGimbal);
            disconnect(this, &Joystick::gimbalControlValue, _activeVehicle, &Vehicle::gimbalControlValue);
            disconnect(this, &Joystick::rcOverride,         _activeVehicle, &Vehicle::sendRCChannelOverride);
        }
        // Always set up the new vehicle
        _activeVehicle = vehicle;
        // If joystick is not calibrated, disable it
        if ( !_calibrated ) {
            vehicle->setJoystickEnabled(false);
        }
        // Update qml in case of joystick transition
        emit calibratedChanged(_calibrated);
        // Build action list
        _buildActionList(vehicle);
        // Only connect the new vehicle if it wants joystick data
        if (vehicle->joystickEnabled()) {
            _pollingStartedForCalibration = false;
            UAS* uas = _activeVehicle->uas();
            connect(this, &Joystick::manualControl, uas, &UAS::setExternalControlSetpoint);
            connect(this, &Joystick::setArmed,           _activeVehicle, &Vehicle::setArmed);
            connect(this, &Joystick::setVtolInFwdFlight, _activeVehicle, &Vehicle::setVtolInFwdFlight);
            connect(this, &Joystick::setFlightMode,      _activeVehicle, &Vehicle::setFlightMode);
            connect(this, &Joystick::gimbalPitchStep,    _activeVehicle, &Vehicle::gimbalPitchStep);
            connect(this, &Joystick::gimbalYawStep,      _activeVehicle, &Vehicle::gimbalYawStep);
            connect(this, &Joystick::centerGimbal,       _activeVehicle, &Vehicle::centerGimbal);
            connect(this, &Joystick::gimbalControlValue, _activeVehicle, &Vehicle::gimbalControlValue);
            connect(this, &Joystick::rcOverride,         _activeVehicle, &Vehicle::sendRCChannelOverride);
            // FIXME: ****
            //connect(this, &Joystick::buttonActionTriggered, uas, &UAS::triggerAction);
        }
    }
    if (!isRunning()) {
        _exitThread = false;
        start();
    }
}

void Joystick::stopPolling(void)
{
    if (isRunning()) {
        if (_activeVehicle && _activeVehicle->joystickEnabled()) {
            UAS* uas = _activeVehicle->uas();
            // Neutral attitude controls
            // emit manualControl(0, 0, 0, 0.5, 0, _activeVehicle->joystickMode());
            disconnect(this, &Joystick::manualControl, uas, &UAS::setExternalControlSetpoint);
            disconnect(this, &Joystick::setArmed,           _activeVehicle, &Vehicle::setArmed);
            disconnect(this, &Joystick::setVtolInFwdFlight, _activeVehicle, &Vehicle::setVtolInFwdFlight);
            disconnect(this, &Joystick::setFlightMode,      _activeVehicle, &Vehicle::setFlightMode);
            disconnect(this, &Joystick::gimbalPitchStep,    _activeVehicle, &Vehicle::gimbalPitchStep);
            disconnect(this, &Joystick::gimbalYawStep,      _activeVehicle, &Vehicle::gimbalYawStep);
            disconnect(this, &Joystick::centerGimbal,       _activeVehicle, &Vehicle::centerGimbal);
            disconnect(this, &Joystick::gimbalControlValue, _activeVehicle, &Vehicle::gimbalControlValue);
            disconnect(this, &Joystick::rcOverride,         _activeVehicle, &Vehicle::sendRCChannelOverride);
        }
        // FIXME: ****
        //disconnect(this, &Joystick::buttonActionTriggered,  uas, &UAS::triggerAction);
        _exitThread = true;
    }
}

void Joystick::setCalibration(int axis, Calibration_t& calibration)
{
    if (!_validAxis(axis)) {
        return;
    }
    _calibrated = true;
    _rgCalibration[axis] = calibration;
    _saveSettings();
    emit calibratedChanged(_calibrated);
}

Joystick::Calibration_t Joystick::getCalibration(int axis)
{
    if (!_validAxis(axis)) {
        return Calibration_t();
    }
    return _rgCalibration[axis];
}

void Joystick::setFunctionAxis(AxisFunction_t function, int axis)
{
    if (!_validAxis(axis)) {
        return;
    }
    _calibrated = true;
    _rgFunctionAxis[function] = axis;
    _saveSettings();
    emit calibratedChanged(_calibrated);
}

int Joystick::getFunctionAxis(AxisFunction_t function)
{
    if (static_cast<int>(function) < 0 || function >= maxFunction) {
        qCWarning(JoystickLog) << "Invalid function" << function;
    }
    return _rgFunctionAxis[function];
}

void Joystick::setButtonRepeat(int button, bool repeat)
{
    if (!_validButton(button) || !_buttonActionArray[button]) {
        return;
    }
    _buttonActionArray[button]->repeat = repeat;
    _buttonActionArray[button]->buttonTime.start();
    //-- Save to settings
    QSettings settings;
    settings.beginGroup(_settingsGroup);
    settings.beginGroup(_name);
    settings.setValue(QString(_buttonActionRepeatKey).arg(button), _buttonActionArray[button]->repeat);
}

bool Joystick::getButtonRepeat(int button)
{
    if (!_validButton(button) || !_buttonActionArray[button]) {
        return false;
    }
    return _buttonActionArray[button]->repeat;
}

void Joystick::_initRCOverrideChannels(const QString& action, bool enable)
{
    //If the button was an RC channel, set the particular RC channel to UINT16_MAX (ignore)
    if (action == _buttonActionGimbalDownRC6 || action == _buttonActionGimbalUpRC6) {
        _rcOverrideChannels[5] = enable ? 1500 : UINT16_MAX;
    }
    else if (action == _buttonActionGimbalLeftRC7 || action == _buttonActionGimbalRightRC7) {
        _rcOverrideChannels[6] = enable ? 1500 : UINT16_MAX;
    }
    else if (action == _buttonActionRC9TriState)  _rcOverrideChannels[8]  = enable ? 1100 : UINT16_MAX;
    else if (action == _buttonActionRC10TriState) _rcOverrideChannels[9]  = enable ? 1100 : UINT16_MAX;
    else if (action == _buttonActionRC11)         _rcOverrideChannels[10] = enable ? 1100 : UINT16_MAX;
    else if (action == _buttonActionRC12)         _rcOverrideChannels[11] = enable ? 1100 : UINT16_MAX;
    else if (action == _buttonActionRC13)         _rcOverrideChannels[12] = enable ? 1100 : UINT16_MAX;
    else if (action == _buttonActionRC14)         _rcOverrideChannels[13] = enable ? 1100 : UINT16_MAX;
    else if (action == _buttonActionRC15)         _rcOverrideChannels[14] = enable ? 1100 : UINT16_MAX;
    else if (action == _buttonActionRC16)         _rcOverrideChannels[15] = enable ? 1100 : UINT16_MAX;
    else if (action == _buttonActionRC17)         _rcOverrideChannels[16] = enable ? 1100 : UINT16_MAX;
    else if (action == _buttonActionRC18)         _rcOverrideChannels[17] = enable ? 1100 : UINT16_MAX;
}

void Joystick::setButtonAction(int button, const QString& action)
{
    if (!_validButton(button)) {
        return;
    }
    qCWarning(JoystickLog) << "setButtonAction:" << button << action;
    QSettings settings;
    settings.beginGroup(_settingsGroup);
    settings.beginGroup(_name);
    if(action.isEmpty() || action == _buttonActionNone) {
        if(_buttonActionArray[button]) {
            _buttonActionArray[button]->deleteLater();
            _buttonActionArray[button] = nullptr;
            //-- Clear from settings
            settings.remove(QString(_buttonActionNameKey).arg(button));
            settings.remove(QString(_buttonActionRepeatKey).arg(button));
            _initRCOverrideChannels(action, false);
        }
    } else {
        if(!_buttonActionArray[button]) {
            _buttonActionArray[button] = new AssignedButtonAction(this, action);
        } else {
            _buttonActionArray[button]->action = action;
            //-- Make sure repeat is off if this action doesn't support repeats
            int idx = _findAssignableButtonAction(action);
            if(idx >= 0) {
                AssignableButtonAction* p = qobject_cast<AssignableButtonAction*>(_assignableButtonActions[idx]);
                if(!p->canRepeat()) {
                    _buttonActionArray[button]->repeat = false;
                }
            }
        }
        //-- Save to settings
        settings.setValue(QString(_buttonActionNameKey).arg(button),   _buttonActionArray[button]->action);
        settings.setValue(QString(_buttonActionRepeatKey).arg(button), _buttonActionArray[button]->repeat);
        _initRCOverrideChannels(action, true);
    }
    emit buttonActionsChanged();
}

QString Joystick::getButtonAction(int button)
{
    if (_validButton(button)) {
        if(_buttonActionArray[button]) {
            return _buttonActionArray[button]->action;
        }
    }
    return QString(_buttonActionNone);
}

QStringList Joystick::buttonActions()
{
    QStringList list;
    for (int button = 0; button < _totalButtonCount; button++) {
        list << getButtonAction(button);
    }
    return list;
}

int Joystick::throttleMode()
{
    return _throttleMode;
}

void Joystick::setThrottleMode(int mode)
{
    if (mode < 0 || mode >= ThrottleModeMax) {
        qCWarning(JoystickLog) << "Invalid throttle mode" << mode;
        return;
    }
    _throttleMode = static_cast<ThrottleMode_t>(mode);
    if (_throttleMode == ThrottleModeDownZero) {
        setAccumulator(false);
    }
    _saveSettings();
    emit throttleModeChanged(_throttleMode);
}

bool Joystick::negativeThrust()
{
    return _negativeThrust;
}

void Joystick::setNegativeThrust(bool allowNegative)
{
    if (_negativeThrust == allowNegative) {
        return;
    }
    _negativeThrust = allowNegative;
    _saveSettings();
    emit negativeThrustChanged(_negativeThrust);
}

float Joystick::exponential()
{
    return _exponential;
}

void Joystick::setExponential(float expo)
{
    _exponential = expo;
    _saveSettings();
    emit exponentialChanged(_exponential);
}

bool Joystick::accumulator()
{
    return _accumulator;
}

void Joystick::setAccumulator(bool accu)
{
    _accumulator = accu;
    _saveSettings();
    emit accumulatorChanged(_accumulator);
}

bool Joystick::deadband()
{
    return _deadband;
}

void Joystick::setDeadband(bool deadband)
{
    _deadband = deadband;
    _saveSettings();
}

bool Joystick::circleCorrection()
{
    return _circleCorrection;
}

void Joystick::setCircleCorrection(bool circleCorrection)
{
    _circleCorrection = circleCorrection;
    _saveSettings();
    emit circleCorrectionChanged(_circleCorrection);
}

bool Joystick::zAxisRC8()
{
    return _useZAxisRC8;
}

void Joystick::setZAxisRC8(bool use)
{
    _useZAxisRC8 = use;
    _saveSettings();
    emit zAxisRC8Changed(_useZAxisRC8);
}

void Joystick::setGimbalEnabled(bool set)
{
    _gimbalEnabled = set;
    _saveSettings();
    emit gimbalEnabledChanged();
}

void Joystick::setAxisFrequency(float val)
{
    //-- Arbitrary limits
    if(val < 0.25f) val = 0.25f;
    if(val > 50.0f) val = 50.0f;
    _axisFrequency = val;
    _saveSettings();
    emit axisFrequencyChanged();
}

void Joystick::setButtonFrequency(float val)
{
    //-- Arbitrary limits
    if(val < 0.25f) val = 0.25f;
    if(val > 50.0f) val = 50.0f;
    _buttonFrequency = val;
    _saveSettings();
    emit buttonFrequencyChanged();
}

void Joystick::setCalibrationMode(bool calibrating)
{
    _calibrationMode = calibrating;
    if (calibrating && !isRunning()) {
        _pollingStartedForCalibration = true;
        startPolling(_multiVehicleManager->activeVehicle());
    }
    else if (_pollingStartedForCalibration) {
        stopPolling();
    }
}


void Joystick::_executeButtonAction(const QString& action, bool buttonDown)
{
    if (!_activeVehicle || !_activeVehicle->joystickEnabled() || action == _buttonActionNone) {
        return;
    }
    if (action == _buttonActionArm) {
        if (buttonDown) emit setArmed(true);
    } else if (action == _buttonActionDisarm) {
        if (buttonDown) emit setArmed(false);
    } else if (action == _buttonActionToggleArm) {
        if (buttonDown) emit setArmed(!_activeVehicle->armed());
    } else if (action == _buttonActionVTOLFixedWing) {
        if (buttonDown) emit setVtolInFwdFlight(true);
    } else if (action == _buttonActionVTOLMultiRotor) {
        if (buttonDown) emit setVtolInFwdFlight(false);
    } else if (_activeVehicle->flightModes().contains(action) || _activeVehicle->extraJoystickFlightModes().contains(action)) {
        if (buttonDown) emit setFlightMode(action);
    } else if(action == _buttonActionContinuousZoomIn || action == _buttonActionContinuousZoomOut) {
        if (buttonDown) {
            emit startContinuousZoom(action == _buttonActionContinuousZoomIn ? 1 : -1);
        } else {
            emit stopContinuousZoom();
        }
    } else if(action == _buttonActionStepZoomIn || action == _buttonActionStepZoomOut) {
        if (buttonDown) emit stepZoom(action == _buttonActionStepZoomIn ? 1 : -1);
    } else if(action == _buttonActionNextStream || action == _buttonActionPreviousStream) {
        if (buttonDown) emit stepStream(action == _buttonActionNextStream ? 1 : -1);
    } else if(action == _buttonActionNextCamera || action == _buttonActionPreviousCamera) {
        if (buttonDown) emit stepCamera(action == _buttonActionNextCamera ? 1 : -1);
    } else if(action == _buttonActionTriggerCamera) {
        if (buttonDown) emit triggerCamera();
    } else if(action == _buttonActionStartVideoRecord) {
        if (buttonDown) emit startVideoRecord();
    } else if(action == _buttonActionStopVideoRecord) {
        if (buttonDown) emit stopVideoRecord();
    } else if(action == _buttonActionToggleVideoRecord) {
        if (buttonDown) emit toggleVideoRecord();
    } else if(action == _buttonActionGimbalUp) {
        if (buttonDown) _pitchStep(1);
    } else if(action == _buttonActionGimbalDown) {
        if (buttonDown) _pitchStep(-1);
    } else if(action == _buttonActionGimbalLeft) {
        if (buttonDown) _yawStep(-1);
    } else if(action == _buttonActionGimbalRight) {
        if (buttonDown) _yawStep(1);
    } else if(action == _buttonActionGimbalCenter) {
        if (buttonDown) {
            _localPitch = 0.0;
            _localYaw   = 0.0;
            emit gimbalControlValue(0.0, 0.0);
        }
    } else if (action == _buttonActionGimbalDownRC6) {
        _rcMomentary(_rcOverrideChannels[5], buttonDown, true, false);
    } else if (action == _buttonActionGimbalUpRC6) {
        _rcMomentary(_rcOverrideChannels[5], buttonDown, true, true);
    } else if (action == _buttonActionGimbalLeftRC7) {
        _rcMomentary(_rcOverrideChannels[6], buttonDown, true, false);
    } else if (action == _buttonActionGimbalRightRC7) {
        _rcMomentary(_rcOverrideChannels[6], buttonDown, true, true);
    } else if (action == _buttonActionRC9TriState) {
        if(buttonDown) _rcTriState(_rcOverrideChannels[8]);
    } else if (action == _buttonActionRC10TriState) {
        if(buttonDown) _rcTriState(_rcOverrideChannels[9]);
    } else if (action == _buttonActionRC11) {
        if (buttonDown) _rcTwoState(_rcOverrideChannels[10]);
    } else if (action == _buttonActionRC12) {
        if (buttonDown) _rcTwoState(_rcOverrideChannels[11]);
    } else if (action == _buttonActionRC13) {
        if (buttonDown) _rcTwoState(_rcOverrideChannels[12]);
    } else if (action == _buttonActionRC14) {
        if (buttonDown) _rcTwoState(_rcOverrideChannels[13]);
    } else if (action == _buttonActionRC15) {
        if (buttonDown) _rcTwoState(_rcOverrideChannels[14]);
    } else if (action == _buttonActionRC16) {
        if (buttonDown) _rcTwoState(_rcOverrideChannels[15]);
    } else if (action == _buttonActionRC17) {
        if (buttonDown) _rcTwoState(_rcOverrideChannels[16]);
    } else if (action == _buttonActionRC18) {
        if (buttonDown) _rcTwoState(_rcOverrideChannels[17]);
    } else if (action == _buttonActionTriButtonKill) {
        _triButtonKillUpdate(buttonDown);
    } else if (action == _buttonActionPlanckTrackLoiterToggle && buttonDown) {
        //Allow transition from Loiter->PlanckTrack and ANY_MODE->Loiter
        emit setFlightMode(_activeVehicle->flightMode() == "Loiter" ? "Planck Track" : "Loiter");
    } else if (action == _buttonActionPlanckTrackAltHoldToggle && buttonDown) {
        //Allow transition from AltHold->PlanckTrack and ANY_MODE->AltHold
        emit setFlightMode(_activeVehicle->flightMode() == "Altitude Hold" ? "Planck Track" : "Altitude Hold");
    } else {
        qCDebug(JoystickLog) << "_buttonAction unknown action:" << action;
    }
}

void Joystick::_triButtonKillUpdate(const bool buttonDown) {
    _triButtonKillState += (buttonDown ? 1 : -1);

    if(_triButtonKillState < 0) _triButtonKillState = 0;
    if(_triButtonKillState > 3) _triButtonKillState = 3;

    if(_triButtonKillState >= 3) {
        _activeVehicle->emergencyStop();
    }
}

void Joystick::_rcMomentary(int& channelValue, bool buttonDown, bool isUpDownPair, bool isUpButton) {
    int highValue = (isUpDownPair && !isUpButton) ? 1100 : 1900;
    int lowValue = isUpDownPair ? 1500 : 1100;
    channelValue = buttonDown ? highValue : lowValue;
}

void Joystick::_rcTwoState(int& channelValue) {
    if(channelValue < 1500) {
        channelValue = 1900;
    } else {
        channelValue = 1100;
    }
}

void Joystick::_rcTriState(int& channelValue) {
    if(channelValue <= 1100) {
        channelValue = 1500;
    } else if(channelValue <= 1500) {
        channelValue = 1900;
    } else {
        channelValue = 1100;
    }
}

void Joystick::_pitchStep(int direction)
{
    _localPitch += static_cast<double>(direction);
    //-- Arbitrary range
    if(_localPitch < -90.0) _localPitch = -90.0;
    if(_localPitch >  35.0) _localPitch =  35.0;
    emit gimbalControlValue(_localPitch, _localYaw);
}

void Joystick::_yawStep(int direction)
{
    _localYaw += static_cast<double>(direction);
    if(_localYaw < -180.0) _localYaw = -180.0;
    if(_localYaw >  180.0) _localYaw =  180.0;
    emit gimbalControlValue(_localPitch, _localYaw);
}

bool Joystick::_validAxis(int axis)
{
    if(axis >= 0 && axis < _axisCount) {
        return true;
    }
    qCWarning(JoystickLog) << "Invalid axis index" << axis;
    return false;
}

bool Joystick::_validButton(int button)
{
    if(button >= 0 && button < _totalButtonCount)
        return true;
    qCWarning(JoystickLog) << "Invalid button index" << button;
    return false;
}

int Joystick::_findAssignableButtonAction(const QString& action)
{
    for(int i = 0; i < _assignableButtonActions.count(); i++) {
        AssignableButtonAction* p = qobject_cast<AssignableButtonAction*>(_assignableButtonActions[i]);
        if(p->action() == action)
            return i;
    }
    return -1;
}

void Joystick::_buildActionList(Vehicle* activeVehicle)
{
    if(_assignableButtonActions.count())
        _assignableButtonActions.clearAndDeleteContents();
    _availableActionTitles.clear();
    //-- Available Actions
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionNone));
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionArm));
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionDisarm));
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionToggleArm));
    if (activeVehicle) {
        QStringList list = activeVehicle->flightModes();
        foreach(auto mode, list) {
            _assignableButtonActions.append(new AssignableButtonAction(this, mode));
        }
        list = activeVehicle->extraJoystickFlightModes();
        foreach(auto mode, list) {
            _assignableButtonActions.append(new AssignableButtonAction(this, mode));
        }
    }
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionVTOLFixedWing));
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionVTOLMultiRotor));
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionContinuousZoomIn, true));
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionContinuousZoomOut, true));
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionStepZoomIn,  true));
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionStepZoomOut, true));
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionNextStream));
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionPreviousStream));
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionNextCamera));
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionPreviousCamera));
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionTriggerCamera));
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionStartVideoRecord));
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionStopVideoRecord));
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionToggleVideoRecord));
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionGimbalDown,    true));
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionGimbalUp,      true));
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionGimbalLeft,    true));
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionGimbalRight,   true));
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionGimbalCenter));
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionGimbalDownRC6));
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionGimbalUpRC6));
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionGimbalLeftRC7));
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionGimbalRightRC7));
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionRC9TriState));
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionRC10TriState));
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionRC11));
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionRC12));
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionRC13));
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionRC14));
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionRC15));
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionRC16));
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionRC17));
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionRC18));
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionTriButtonKill));
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionPlanckTrackLoiterToggle));
    _assignableButtonActions.append(new AssignableButtonAction(this, _buttonActionPlanckTrackAltHoldToggle));
    for(int i = 0; i < _assignableButtonActions.count(); i++) {
        AssignableButtonAction* p = qobject_cast<AssignableButtonAction*>(_assignableButtonActions[i]);
        _availableActionTitles << p->action();
    }
    emit assignableActionsChanged();
}
