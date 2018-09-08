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
#include "AirspaceFlightListProvider.h"

#include "airmap/flight.h"

#include <QObject>
#include <QDateTime>

//-----------------------------------------------------------------------------
class AirMapFlightInfo : public AirspaceFlightInfo
{
    Q_OBJECT
public:
    AirMapFlightInfo                        (const airmap::Flight& flight, QObject *parent = nullptr);
    QString             flightID            () override { return QString::fromStdString(_flight.id); }
    QString             flightPlanID        () override { return _flight.flight_plan_id ? QString::fromStdString(_flight.flight_plan_id.get()) : QString(); }
    QString             createdTime         () override;
    QString             startTime           () override;
    QString             endTime             () override;
    QDateTime           qStartTime          () override;
    QGeoCoordinate      takeOff             () override { return QGeoCoordinate(static_cast<double>(_flight.latitude), static_cast<double>(_flight.longitude));}
    QVariantList        boundingBox         () override { return _boundingBox; }
    bool                active              () override;
    void                setEndFlight        (airmap::DateTime end);
private:
    airmap::Flight      _flight;
    QVariantList        _boundingBox;
};

//-----------------------------------------------------------------------------
/**
 * @class AirspaceFlightListManager
 * Base class for flight list management
 */

class AirMapFlightListManager : public AirspaceFlightListProvider, public LifetimeChecker {
    Q_OBJECT
public:
    AirMapFlightListManager                 (AirMapSharedState &shared, QObject* parent = nullptr);

    AirspaceFlightModel*flightList          () override { return &_flightList; }
    void                loadFlightList      (QDateTime startTime, QDateTime endTime) override;
    void                endFlight           (QString flightID) override;
    bool                loadingFlightList   () override { return _loadingFlightList; }

signals:
    void                error               (const QString& what, const QString& airmapdMessage, const QString& airmapdDetails);

private slots:
    void _endFlight                         ();
    void _loadFlightList                    ();

private:

    enum class State {
        Idle,
        GetPilotID,
        FlightUpload,
        FlightUpdate,
        FlightEnd,
        FlightSubmit,
        FlightPolling,
        LoadFlightList,
    };

    State                   _state = State::Idle;
    AirMapSharedState&      _shared;
    QString                 _flightToEnd;
    QDateTime               _rangeStart;
    QDateTime               _rangeEnd;
    bool                    _loadingFlightList = false;
    AirspaceFlightModel     _flightList;
};
