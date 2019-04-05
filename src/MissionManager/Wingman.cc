/****************************************************************************
 *
 *   (c) 2009-2016 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#include "Wingman.h"
#include "QGCGeo.h"
#include "QGCQGeoCoordinate.h"
#include "QGCApplication.h"

#include <QGeoRectangle>
#include <QDebug>
#include <QJsonArray>
#include <QLineF>
#include <QFile>
#include <QDomDocument>

Wingman::Wingman(QObject* parent)
    : QObject               (parent)
    , _dirty                (false)
    , _interactive          (false)
{
    _init();
}

void Wingman::_init(void)
{
 //   connect(&_polylineModel, &QmlObjectListModel::dirtyChanged, this, &Wingman::_polylineModelDirtyChanged);
 //   connect(&_polylineModel, &QmlObjectListModel::countChanged, this, &Wingman::_polylineModelCountChanged);
}

void Wingman::clear(void)
{
    _polylinePath.clear();
    emit pathChanged();

 //   _polylineModel.clearAndDeleteContents();

    emit cleared();

    setDirty(true);
}

void Wingman::setDirty(bool dirty)
{
    if (_dirty != dirty) {
        _dirty = dirty;
        if (!dirty) {
    //        _polylineModel.setDirty(false);
        }
    //    emit dirtyChanged(dirty);
    }
}
QGeoCoordinate Wingman::_coordFromPointF(const QPointF& point) const
{
    QGeoCoordinate coord;

    if (_polylinePath.count() > 0) {
        QGeoCoordinate tangentOrigin = _polylinePath[0].value<QGeoCoordinate>();
        convertNedToGeo(-point.y(), point.x(), 0, tangentOrigin, &coord);
    }

    return coord;
}

QPointF Wingman::_pointFFromCoord(const QGeoCoordinate& coordinate) const
{
    if (_polylinePath.count() > 0) {
        double y, x, down;
        QGeoCoordinate tangentOrigin = _polylinePath[0].value<QGeoCoordinate>();

        convertGeoToNed(coordinate, tangentOrigin, &y, &x, &down);
        return QPointF(x, -y);
    }

    return QPointF();
}

void Wingman::setPath(const QList<QGeoCoordinate>& path)
{
    _polylinePath.clear();
 //   _polylineModel.clearAndDeleteContents();
    for (const QGeoCoordinate& coord: path) {
        _polylinePath.append(QVariant::fromValue(coord));
  //      _polylineModel.append(new QGCQGeoCoordinate(coord, this));
    }

    setDirty(true);
    emit pathChanged();
}

void Wingman::setPath(const QVariantList& path)
{
    _polylinePath = path;

 //   _polylineModel.clearAndDeleteContents();
  //  for (int i=0; i<_polylinePath.count(); i++) {
 //       _polylineModel.append(new QGCQGeoCoordinate(_polylinePath[i].value<QGeoCoordinate>(), this));
  //  }

    setDirty(true);
    emit pathChanged();
}

QList<QGeoCoordinate> Wingman::coordinateList(void) const
{
    QList<QGeoCoordinate> coords;

    for (int i=0; i<_polylinePath.count(); i++) {
        coords.append(_polylinePath[i].value<QGeoCoordinate>());
    }

    return coords;
}

void Wingman::updateGCSLocation(const QGeoCoordinate& coordinate)
{
    _polylinePath[0] = QVariant::fromValue(coordinate);
    QGeoCoordinate wingman_setpoint;
    convertNedToGeo(10, 10, 10, coordinate, &wingman_setpoint);
    qDebug() << "test";
    _polylinePath[1] = QVariant::fromValue(wingman_setpoint);
}

void Wingman::setInteractive(bool interactive)
{
    if (_interactive != interactive) {
        _interactive = interactive;
        emit interactiveChanged(interactive);
    }
}

void Wingman::_polylineModelDirtyChanged(bool dirty)
{
    if (dirty) {
        setDirty(true);
    }
}

void Wingman::_polylineModelCountChanged(int count)
{
    emit countChanged(count);
}

double Wingman::length(void) const
{
    double length = 0;

    for (int i=0; i<_polylinePath.count() - 1; i++) {
        QGeoCoordinate from = _polylinePath[i].value<QGeoCoordinate>();
        QGeoCoordinate to = _polylinePath[i+1].value<QGeoCoordinate>();
        length += from.distanceTo(to);
    }

    return length;
}
