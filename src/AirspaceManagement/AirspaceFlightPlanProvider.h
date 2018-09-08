/****************************************************************************
 *
 *   (c) 2017 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#pragma once

/**
 * @file AirspaceFlightPlanProvider.h
 * Create and maintain a flight plan
 */

#include "AirspaceAdvisoryProvider.h"
#include "QmlObjectListModel.h"

#include <QObject>
#include <QDateTime>
#include <QAbstractListModel>

class PlanMasterController;

//-----------------------------------------------------------------------------
class AirspaceFlightAuthorization : public QObject
{
    Q_OBJECT
public:
    AirspaceFlightAuthorization                     (QObject *parent = nullptr);

    enum AuthorizationStatus {
        Accepted,
        Rejected,
        Pending,
        AcceptedOnSubmission,
        RejectedOnSubmission,
        Unknown
    };

    Q_ENUM(AuthorizationStatus)

    Q_PROPERTY(QString              name            READ name           CONSTANT)
    Q_PROPERTY(QString              id              READ id             CONSTANT)
    Q_PROPERTY(AuthorizationStatus  status          READ status         CONSTANT)
    Q_PROPERTY(QString              message         READ message        CONSTANT)

    virtual QString                 name            () = 0;
    virtual QString                 id              () = 0;
    virtual AuthorizationStatus     status          () = 0;
    virtual QString                 message         () = 0;

};


//-----------------------------------------------------------------------------
class AirspaceFlightPlanProvider : public QObject
{
    Q_OBJECT
public:

    enum PermitStatus {
        PermitNone = 0,     //-- No flght plan
        PermitPending,
        PermitAccepted,
        PermitRejected,
        PermitNotRequired,
    };

    Q_ENUM(PermitStatus)

    AirspaceFlightPlanProvider                      (QObject *parent = nullptr);

    ///< Flight Planning and Filing
    Q_PROPERTY(QDateTime            flightStartTime         READ flightStartTime    WRITE  setFlightStartTime   NOTIFY flightStartTimeChanged)      ///< Start of flight
    Q_PROPERTY(int                  flightDuration          READ flightDuration     WRITE  setFlightDuration    NOTIFY flightDurationChanged)       ///< Flight Duration
    Q_PROPERTY(bool                 flightStartsNow         READ flightStartsNow    WRITE  setFlightStartsNow   NOTIFY flightStartsNowChanged)

    ///< Flight Briefing
    Q_PROPERTY(PermitStatus         flightPermitStatus      READ flightPermitStatus                             NOTIFY flightPermitStatusChanged)   ///< State of flight permission
    Q_PROPERTY(bool                 valid                   READ valid                                          NOTIFY advisoryChanged)
    Q_PROPERTY(QmlObjectListModel*  advisories              READ advisories                                     NOTIFY advisoryChanged)
    Q_PROPERTY(QmlObjectListModel*  ruleSets                READ ruleSets                                       NOTIFY advisoryChanged)
    Q_PROPERTY(QGCGeoBoundingCube*  missionArea             READ missionArea                                    NOTIFY missionAreaChanged)
    Q_PROPERTY(AirspaceAdvisoryProvider::AdvisoryColor airspaceColor READ airspaceColor                         NOTIFY advisoryChanged)
    Q_PROPERTY(QmlObjectListModel*  rulesViolation          READ rulesViolation                                 NOTIFY rulesChanged)
    Q_PROPERTY(QmlObjectListModel*  rulesInfo               READ rulesInfo                                      NOTIFY rulesChanged)
    Q_PROPERTY(QmlObjectListModel*  rulesReview             READ rulesReview                                    NOTIFY rulesChanged)
    Q_PROPERTY(QmlObjectListModel*  rulesFollowing          READ rulesFollowing                                 NOTIFY rulesChanged)
    Q_PROPERTY(QmlObjectListModel*  briefFeatures           READ briefFeatures                                  NOTIFY rulesChanged)
    Q_PROPERTY(QmlObjectListModel*  authorizations          READ authorizations                                 NOTIFY rulesChanged)

    //-- TODO: This will submit the current flight plan in memory.
    Q_INVOKABLE virtual void    submitFlightPlan            () = 0;
    Q_INVOKABLE virtual void    updateFlightPlan            () = 0;

    virtual PermitStatus        flightPermitStatus  () const { return PermitNone; }
    virtual QDateTime           flightStartTime     () const = 0;
    virtual int                 flightDuration      () const = 0;
    virtual bool                flightStartsNow     () const = 0;
    virtual QGCGeoBoundingCube* missionArea         () = 0;
    virtual bool                valid               () = 0;                     ///< Current advisory list is valid
    virtual QmlObjectListModel* advisories          () = 0;                     ///< List of AirspaceAdvisory
    virtual QmlObjectListModel* ruleSets            () = 0;                     ///< List of AirspaceRuleSet
    virtual AirspaceAdvisoryProvider::AdvisoryColor  airspaceColor () = 0;      ///< Aispace overall color

    virtual QmlObjectListModel* rulesViolation      () = 0;                     ///< List of AirspaceRule in violation
    virtual QmlObjectListModel* rulesInfo           () = 0;                     ///< List of AirspaceRule need more information
    virtual QmlObjectListModel* rulesReview         () = 0;                     ///< List of AirspaceRule should review
    virtual QmlObjectListModel* rulesFollowing      () = 0;                     ///< List of AirspaceRule following
    virtual QmlObjectListModel* briefFeatures       () = 0;                     ///< List of AirspaceRule in violation
    virtual QmlObjectListModel* authorizations      () = 0;                     ///< List of AirspaceFlightAuthorization

    virtual void                setFlightStartTime  (QDateTime start) = 0;
    virtual void                setFlightDuration   (int seconds) = 0;
    virtual void                setFlightStartsNow  (bool now) = 0;
    virtual void                startFlightPlanning (PlanMasterController* planController) = 0;

signals:
    void flightPermitStatusChanged                  ();
    void flightStartTimeChanged                     ();
    void flightStartsNowChanged                     ();
    void flightDurationChanged                      ();
    void advisoryChanged                            ();
    void missionAreaChanged                         ();
    void rulesChanged                               ();
};
