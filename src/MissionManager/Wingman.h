/****************************************************************************
 *
 *   (c) 2009-2016 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#pragma once

#include <QObject>
#include <QGeoCoordinate>
#include <QVariantList>

#include "QmlObjectListModel.h"

class Wingman : public QObject
{
    Q_OBJECT

public:
    Wingman(QObject* parent = NULL);

    Q_PROPERTY(int                  count       READ count                                  NOTIFY countChanged)
    Q_PROPERTY(QVariantList         path        READ path                                   NOTIFY pathChanged)
 //   Q_PROPERTY(QmlObjectListModel*  pathModel   READ qmlPathModel                           CONSTANT)
    Q_PROPERTY(bool                 dirty       READ dirty          WRITE setDirty          NOTIFY dirtyChanged)
    Q_PROPERTY(bool                 interactive READ interactive    WRITE setInteractive    NOTIFY interactiveChanged)

    Q_PROPERTY(QGeoCoordinate       gcsLocation READ gcsLocation    WRITE updateGCSLocation NOTIFY gcsLocationChanged)
    Q_PROPERTY(QGeoCoordinate       setpoint    READ setpoint                               NOTIFY setpointChanged)
 //   Q_PROPERTY(QReal                 north_offset WRITE setNorthOffset)   // Meters north
 //   Q_PROPERTY(QReal                 east_offset  WRITE setEastOffset)    // Meters east

    Q_INVOKABLE void clear(void);
    //Q_INVOKABLE void appendVertex(const QGeoCoordinate& coordinate);
    //Q_INVOKABLE void removeVertex(int vertexIndex);
    Q_INVOKABLE void updateGCSLocation(const QGeoCoordinate& coordinate);

    /// Returns the path in a list of QGeoCoordinate's format
    QList<QGeoCoordinate> coordinateList(void) const;

    /// Convert polyline to NED and return (D is ignored)
    QList<QPointF> nedPolyline(void);

    /// Returns the length of the polyline in meters
    double length(void) const;

    // Property methods

    int             count       (void) const { return _polylinePath.count(); }
    bool            dirty       (void) const { return _dirty; }
    void            setDirty    (bool dirty);
    bool            interactive (void) const { return _interactive; }
    QVariantList    path        (void) const { return _polylinePath; }
    QGeoCoordinate  setpoint    (void) const { return _setpoint; }
    QGeoCoordinate  gcsLocation (void) const { return _gcsLocation; }


//    QmlObjectListModel* qmlPathModel(void) { return &_polylineModel; }
//    QmlObjectListModel& pathModel   (void) { return _polylineModel; }

    void setPath        (const QList<QGeoCoordinate>& path);
    void setPath        (const QVariantList& path);
    void setInteractive (bool interactive);

signals:
    void countChanged       (int count);
    void pathChanged        (void);
    void dirtyChanged       (bool dirty);
    void cleared            (void);
    void interactiveChanged (bool interactive);
    void setpointChanged    (QGeoCoordinate setpoint);
    void gcsLocationChanged (QGeoCoordinate location);

private slots:
    void _polylineModelCountChanged(int count);
    void _polylineModelDirtyChanged(bool dirty);

private:
    void _init(void);
    QGeoCoordinate _coordFromPointF(const QPointF& point) const;
    QPointF _pointFFromCoord(const QGeoCoordinate& coordinate) const;

    QVariantList        _polylinePath;
 //   QmlObjectListModel  _polylineModel;
    bool                _dirty;
    bool                _interactive;
    QGeoCoordinate      _setpoint;
    QGeoCoordinate      _gcsLocation;
};
