/****************************************************************************
 *
 *   (c) 2017 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#pragma once

#include <QObject>
#include <QAbstractListModel>
#include <QGeoCoordinate>
#include <QDateTime>

class Vehicle;

//-----------------------------------------------------------------------------
class AirspaceFlightInfo : public QObject
{
    Q_OBJECT
public:
    AirspaceFlightInfo                              (QObject *parent = nullptr);

    Q_PROPERTY(QString              flightID        READ flightID       CONSTANT)
    Q_PROPERTY(QString              flightPlanID    READ flightPlanID   CONSTANT)
    Q_PROPERTY(QString              createdTime     READ createdTime    CONSTANT)
    Q_PROPERTY(QString              startTime       READ startTime      CONSTANT)
    Q_PROPERTY(QString              endTime         READ endTime        CONSTANT)
    Q_PROPERTY(QGeoCoordinate       takeOff         READ takeOff        CONSTANT)
    Q_PROPERTY(QVariantList         boundingBox     READ boundingBox    CONSTANT)
    Q_PROPERTY(bool                 active          READ active         NOTIFY activeChanged)

    virtual QString                 flightID        () = 0;
    virtual QString                 flightPlanID    () = 0;
    virtual QString                 createdTime     () = 0;
    virtual QString                 startTime       () = 0;
    virtual QDateTime               qStartTime      () = 0;
    virtual QString                 endTime         () = 0;
    virtual QGeoCoordinate          takeOff         () = 0;
    virtual QVariantList            boundingBox     () = 0;
    virtual bool                    active          () = 0;

signals:
    void    activeChanged                           ();
};

//-----------------------------------------------------------------------------
class AirspaceFlightModel : public QAbstractListModel
{
    Q_OBJECT
public:

    enum QGCLogModelRoles {
        ObjectRole = Qt::UserRole + 1
    };

    AirspaceFlightModel         (QObject *parent = nullptr);

    Q_PROPERTY(int count READ count NOTIFY countChanged)

    Q_INVOKABLE AirspaceFlightInfo* get                 (int index);
    Q_INVOKABLE int                 findFlightID        (QString flightID);

    int         count           () const;
    void        append          (AirspaceFlightInfo *entry);
    void        remove          (const QString& flightID);
    void        remove          (int index);
    void        clear           ();
    void        sortStartFlight ();

    AirspaceFlightInfo*
                operator[]      (int i);

    int         rowCount        (const QModelIndex & parent = QModelIndex()) const;
    QVariant    data            (const QModelIndex & index, int role = Qt::DisplayRole) const;

signals:
    void        countChanged    ();

protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<AirspaceFlightInfo*> _flightEntries;
};

//-----------------------------------------------------------------------------
/**
 * @class AirspaceFlightListProvider
 * Base class for flight list management
 */

class AirspaceFlightListProvider : public QObject {
    Q_OBJECT
public:
    AirspaceFlightListProvider              (QObject* parent = nullptr);
    virtual ~AirspaceFlightListProvider     ();

    Q_PROPERTY(AirspaceFlightModel* flightList              READ flightList             NOTIFY flightListChanged)
    Q_PROPERTY(bool                 loadingFlightList       READ loadingFlightList      NOTIFY loadingFlightListChanged)

    Q_INVOKABLE virtual void    loadFlightList      (QDateTime startTime, QDateTime endTime) = 0;
    Q_INVOKABLE virtual void    endFlight           (QString flighID) = 0;

    virtual AirspaceFlightModel*flightList          () = 0;                     ///< List of AirspaceFlightInfo
    virtual bool                loadingFlightList   () = 0;

signals:
    void flightListChanged                          ();
    void loadingFlightListChanged                   ();

};
