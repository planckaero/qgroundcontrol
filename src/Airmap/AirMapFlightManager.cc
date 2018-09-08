/****************************************************************************
 *
 *   (c) 2009-2016 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#include "AirMapFlightManager.h"
#include "AirMapManager.h"
#include "AirMapRulesetsManager.h"
#include "QGCApplication.h"

#include "QGCMAVLink.h"

#include "airmap/pilots.h"
#include "airmap/flights.h"
#include "airmap/date_time.h"
#include "airmap/flight_plans.h"
#include "airmap/geometry.h"

using namespace airmap;

//-----------------------------------------------------------------------------
AirMapFlightManager::AirMapFlightManager(AirMapSharedState& shared)
    : _shared(shared)
{

}

//-----------------------------------------------------------------------------
void
AirMapFlightManager::endFlight(const QString& flightID)
{
    if (_state != State::Idle) {
        qCWarning(AirMapManagerLog) << "AirMapFlightManager::endFlight: State not idle";
        return;
    }
    qCDebug(AirMapManagerLog) << "Ending flight" << flightID;
    _state = State::FlightEnd;
    Flights::EndFlight::Parameters params;
    params.authorization = _shared.loginToken().toStdString();
    params.id = flightID.toStdString();
    std::weak_ptr<LifetimeChecker> isAlive(_instance);
    _shared.client()->flights().end_flight(params, [this, isAlive](const Flights::EndFlight::Result& result) {
        if (!isAlive.lock()) return;
        if (_state != State::FlightEnd) return;
        _state = State::Idle;
        if (!result) {
            QString description = QString::fromStdString(result.error().description() ? result.error().description().get() : "");
            emit error("Failed to end Flight",
                    QString::fromStdString(result.error().message()), description);
        }
    });
}


