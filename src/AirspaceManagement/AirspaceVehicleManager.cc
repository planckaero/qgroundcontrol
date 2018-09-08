/****************************************************************************
 *
 *   (c) 2017 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/


#include "AirspaceManager.h"
#include "AirspaceVehicleManager.h"
#include "QGCApplication.h"
#include "Vehicle.h"
#include "MissionItem.h"

//-----------------------------------------------------------------------------
AirspaceVehicleManager::AirspaceVehicleManager(const Vehicle& vehicle)
    : _vehicle(vehicle)
{
    qCDebug(AirspaceManagementLog) << "Instatiating AirspaceVehicleManager";
    connect(&_vehicle, &Vehicle::armedChanged,           this, &AirspaceVehicleManager::_vehicleArmedChanged);
    connect(&_vehicle, &Vehicle::mavlinkMessageReceived, this, &AirspaceVehicleManager::vehicleMavlinkMessageReceived);
}

//-----------------------------------------------------------------------------
AirspaceVehicleManager::~AirspaceVehicleManager()
{
    if(_flightPlan) {
        delete _flightPlan;
    }
}

//-----------------------------------------------------------------------------
void
AirspaceVehicleManager::init()
{
    //-- Flight planner for this vehicle
    _flightPlan = _instantiateAirspaceFlightPlanProvider();
}

//-----------------------------------------------------------------------------
void
AirspaceVehicleManager::setROI(const QGeoCoordinate& pointNW, const QGeoCoordinate& pointSE, bool planView, bool reset)
{
    if(planView) {
        //-- Is there a mission?
        if(_flightPlan->flightPermitStatus() != AirspaceFlightPlanProvider::PermitNone) {
            //-- Is there a polygon to work with?
            if(_flightPlan->missionArea()->isValid() && _flightPlan->missionArea()->area() > 0.0) {
                qgcApp()->toolbox()->airspaceManager()->setROI(*_flightPlan->missionArea(), reset);
                return;
            }
        }
    }
    //-- Use screen coordinates (what you see is what you get)
    qgcApp()->toolbox()->airspaceManager()->setROI(QGCGeoBoundingCube(pointNW, pointSE));
}

//-----------------------------------------------------------------------------
void
AirspaceVehicleManager::_vehicleArmedChanged(bool armed)
{
    if (armed) {
        qCDebug(AirspaceManagementLog) << "Starting telemetry";
        startTelemetryStream();
        _vehicleWasInMissionMode = _vehicle.flightMode() == _vehicle.missionFlightMode();
    } else {
        qCDebug(AirspaceManagementLog) << "Stopping telemetry";
        stopTelemetryStream();
        // end the flight if we were in mission mode during arming or disarming
        // TODO: needs to be improved. for instance if we do RTL and then want to continue the mission...
        if (_vehicleWasInMissionMode || _vehicle.flightMode() == _vehicle.missionFlightMode()) {
            endFlight();
        }
    }
}

