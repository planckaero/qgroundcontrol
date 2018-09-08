/****************************************************************************
 *
 *   (c) 2017 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#pragma once

#include "LifetimeChecker.h"
#include "AirMapSharedState.h"
#include "AirspaceFlightPlanProvider.h"

#include <QTimer>
#include <QObject>
#include <QList>
#include <QGeoCoordinate>

//-----------------------------------------------------------------------------
/// WIP: This is a "per vehicle" instance with the idea that you can have
/// multiple vehicles and each maintain its own flights. That's not the
/// case yet. Flight plan/submission is still done by AirMapFlightPlanManager,
/// which is a singleton.
///
class AirMapFlightManager : public QObject, public LifetimeChecker
{
    Q_OBJECT
public:
    AirMapFlightManager             (AirMapSharedState& shared);

    void    endFlight               (const QString& id);

signals:
    void    error                   (const QString& what, const QString& airmapdMessage, const QString& airmapdDetails);

private:

    enum class State {
        Idle,
        FlightEnd,
    };

    State                           _state = State::Idle;
    AirMapSharedState&              _shared;
    QString                         _flightID;
    QGCGeoBoundingCube              _searchArea;
};

