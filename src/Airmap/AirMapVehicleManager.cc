/****************************************************************************
 *
 *   (c) 2009-2016 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#include "AirspaceFlightListProvider.h"
#include "AirspaceFlightPlanProvider.h"
#include "AirMapFlightPlanManager.h"
#include "AirMapVehicleManager.h"
#include "AirMapManager.h"

#include "QGCApplication.h"
#include "Vehicle.h"
#include "QGCApplication.h"
#include "SettingsManager.h"

//-----------------------------------------------------------------------------
AirMapVehicleManager::AirMapVehicleManager(AirMapSharedState& shared, const Vehicle& vehicle)
    : AirspaceVehicleManager(vehicle)
    , _shared(shared)
    , _telemetry(shared)
    , _trafficMonitor(shared)
{
    connect(&_telemetry,      &AirMapTelemetry::error,                          this, &AirMapVehicleManager::error);
    connect(&_trafficMonitor, &AirMapTrafficMonitor::error,                     this, &AirMapVehicleManager::error);
    connect(&_trafficMonitor, &AirMapTrafficMonitor::trafficUpdate,             this, &AirspaceVehicleManager::trafficUpdate);
}

//-----------------------------------------------------------------------------
void
AirMapVehicleManager::init()
{
    AirspaceVehicleManager::init();
    AirMapFlightPlanManager* planMgr = qobject_cast<AirMapFlightPlanManager*>(flightPlan());
    if(planMgr) {
        connect(planMgr,      &AirMapFlightPlanManager::flightIDChanged,        this, &AirMapVehicleManager::_flightIDChanged);
    }
}

//-----------------------------------------------------------------------------
void
AirMapVehicleManager::startTelemetryStream()
{
    AirMapFlightPlanManager* planMgr = qobject_cast<AirMapFlightPlanManager*>(flightPlan());
    if (!planMgr->flightID().isEmpty()) {
        //-- Is telemetry enabled?
        if(qgcApp()->toolbox()->settingsManager()->airMapSettings()->enableTelemetry()->rawValue().toBool()) {
            //-- TODO: This will start telemetry using the current flight ID in memory (current flight in AirMapFlightPlanManager)
            qCDebug(AirMapManagerLog) << "AirMap telemetry stream enabled";
            _telemetry.startTelemetryStream(planMgr->flightID());
        }
    } else {
        qCDebug(AirMapManagerLog) << "AirMap telemetry stream not possible (No Flight ID)";
    }
}

//-----------------------------------------------------------------------------
void
AirMapVehicleManager::stopTelemetryStream()
{
    _telemetry.stopTelemetryStream();
}

//-----------------------------------------------------------------------------
bool
AirMapVehicleManager::isTelemetryStreaming()
{
    return _telemetry.isTelemetryStreaming();
}

//-----------------------------------------------------------------------------
void
AirMapVehicleManager::endFlight()
{
    AirMapFlightPlanManager* pPlan = qobject_cast<AirMapFlightPlanManager*>(flightPlan());
    if (pPlan && !pPlan->flightID().isEmpty()) {
        qgcApp()->toolbox()->airspaceManager()->flights()->endFlight(pPlan->flightID());
    }
    _trafficMonitor.stop();
}

//-----------------------------------------------------------------------------
void
AirMapVehicleManager::vehicleMavlinkMessageReceived(const mavlink_message_t& message)
{
    if (isTelemetryStreaming()) {
        _telemetry.vehicleMessageReceived(message);
    }
}

//-----------------------------------------------------------------------------
void
AirMapVehicleManager::_error(const QString& what, const QString& airmapdMessage, const QString& airmapdDetails)
{
    qCDebug(AirMapManagerLog) << "Error: " << what << ", msg: " << airmapdMessage << ", details: " << airmapdDetails;
    qgcApp()->showMessage(QString("Error: %1. %2").arg(what).arg(airmapdMessage));
}

//-----------------------------------------------------------------------------
AirspaceFlightPlanProvider*
AirMapVehicleManager::_instantiateAirspaceFlightPlanProvider()
{
    AirMapFlightPlanManager* flightPlan = new AirMapFlightPlanManager(_shared);
    connect(flightPlan, &AirMapFlightPlanManager::error, this, &AirMapVehicleManager::_error);
    return flightPlan;
}

//-----------------------------------------------------------------------------
void
AirMapVehicleManager::_flightIDChanged(QString flightID)
{
    qCDebug(AirMapManagerLog) << "Flight ID Changed:" << flightID << this;
    //-- Handle traffic monitor
    if(flightID.isEmpty()) {
        _trafficMonitor.stop();
    } else {
        qCDebug(AirMapManagerLog) << "Starting traffic updates for" << flightID << "at" << QDateTime::currentDateTime() << "(Flight to start at:" << flightPlan()->flightStartTime() << ")";
        _trafficMonitor.startConnection(flightID);
    }
}
