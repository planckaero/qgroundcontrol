#pragma once
#include <QList>
#include <QtPositioning/qgeopositioninfosource.h>

class PositionHistory
{
public:
    PositionHistory(int max_length = 100, double min_distance_between_points = 50., double min_seconds_between_points = 30.);

    void push_position(QGeoPositionInfo position);

    QList<QGeoPositionInfo> get_full_history(void);

    QList<QGeoPositionInfo> get_history_until(QDateTime oldest);
    QList<QGeoPositionInfo> get_history_until(double max_age_seconds);

private:
   QList<QGeoPositionInfo> _track_history;
   int _max_length;
   double _min_dist;
   double _min_secs;
};
