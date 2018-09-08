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

#include <QObject>
#include <QTimer>
#include <QList>
#include <QGeoCoordinate>

#include "airmap/flight.h"
#include "airmap/flight_plan.h"
#include "airmap/ruleset.h"

class AirMapRuleFeature;
class PlanMasterController;

//-----------------------------------------------------------------------------
class AirMapFlightAuthorization : public AirspaceFlightAuthorization
{
    Q_OBJECT
public:
    AirMapFlightAuthorization               (const airmap::Evaluation::Authorization auth, QObject *parent = nullptr);

    AirspaceFlightAuthorization::AuthorizationStatus
                            status          () override;
    QString                 name            () override { return QString::fromStdString(_auth.authority.name); }
    QString                 id              () override { return QString::fromStdString(_auth.authority.id); }
    QString                 message         () override { return QString::fromStdString(_auth.message); }
private:
    airmap::Evaluation::Authorization   _auth;
};

//-----------------------------------------------------------------------------
/// class to upload a flight
class AirMapFlightPlanManager : public AirspaceFlightPlanProvider, public LifetimeChecker
{
    Q_OBJECT
public:
    AirMapFlightPlanManager                 (AirMapSharedState& shared, QObject *parent = nullptr);
    ~AirMapFlightPlanManager                () override;

    PermitStatus        flightPermitStatus  () const override { return _flightPermitStatus; }
    QDateTime           flightStartTime     () const override;
    int                 flightDuration      () const override;
    bool                flightStartsNow     () const override { return _flightStartsNow; }
    bool                valid               () override { return _valid; }
    QmlObjectListModel* advisories          () override { return &_advisories; }
    QmlObjectListModel* ruleSets            () override { return &_rulesets; }
    QGCGeoBoundingCube* missionArea         () override { return &_flight.bc; }

    AirspaceAdvisoryProvider::AdvisoryColor
                        airspaceColor       () override { return _airspaceColor; }

    QmlObjectListModel* rulesViolation      () override { return &_rulesViolation; }
    QmlObjectListModel* rulesInfo           () override { return &_rulesInfo; }
    QmlObjectListModel* rulesReview         () override { return &_rulesReview; }
    QmlObjectListModel* rulesFollowing      () override { return &_rulesFollowing; }
    QmlObjectListModel* briefFeatures       () override { return &_briefFeatures; }
    QmlObjectListModel* authorizations      () override { return &_authorizations; }
    QString             flightPlanID        () {return QString::fromStdString(_flightPlan.id); }
    QString             flightID            () {return _flightId; }

    void                updateFlightPlan    () override;
    void                submitFlightPlan    () override;
    void                startFlightPlanning (PlanMasterController* planController) override;
    void                stopFlightPlanning  () override;
    void                setFlightStartTime  (QDateTime start) override;
    void                setFlightDuration   (int seconds) override;
    void                setFlightStartsNow  (bool now) override;

signals:
    void            error                   (const QString& what, const QString& airmapdMessage, const QString& airmapdDetails);
    void            flightIDChanged         (QString flightID);

private slots:
    void _pollBriefing                      ();
    void _missionChanged                    ();
    void _uploadFlightPlan                  ();
    void _updateFlightPlanOnTimer           ();

private:
    void _createFlightPlan                  ();
    bool _collectFlightDtata                ();
    void _updateFlightPlan                  (bool interactive = false);
    bool _findBriefFeature                  (const QString& name);
    void _updateFlightStartEndTime          (airmap::DateTime& start_time, airmap::DateTime& end_time);
    void _updateRulesAndFeatures            (std::vector<airmap::RuleSet::Id>& rulesets, std::unordered_map<std::string, airmap::RuleSet::Feature::Value>& features, bool updateFeatures = false);

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

    struct Flight {
        QGCGeoBoundingCube bc;
        QList<QGeoCoordinate> coords;
        QGeoCoordinate  takeoffCoord;
        float maxAltitude = 0;
        void reset() {
            bc.reset();
            coords.clear();
            maxAltitude = 0;
        }
    };

    Flight                  _flight;                ///< flight pending to be uploaded
    State                   _state = State::Idle;
    AirMapSharedState&      _shared;
    QTimer                  _pollTimer;             ///< timer to poll for approval check
    QString                 _flightId;              ///< Current flight ID, not necessarily accepted yet
    PlanMasterController*   _planController = nullptr;
    bool                    _valid = false;
    bool                    _flightStartsNow = false;
    QmlObjectListModel      _advisories;
    QmlObjectListModel      _rulesets;
    QmlObjectListModel      _rulesViolation;
    QmlObjectListModel      _rulesInfo;
    QmlObjectListModel      _rulesReview;
    QmlObjectListModel      _rulesFollowing;
    QmlObjectListModel      _briefFeatures;
    QmlObjectListModel      _authorizations;
    airmap::FlightPlan      _flightPlan;
    QDateTime               _flightStartTime;
    int                     _flightDuration = 15 * 60;

    QList<AirMapRuleFeature*> _importantFeatures;

    AirspaceAdvisoryProvider::AdvisoryColor  _airspaceColor;
    AirspaceFlightPlanProvider::PermitStatus _flightPermitStatus = AirspaceFlightPlanProvider::PermitNone;

};

