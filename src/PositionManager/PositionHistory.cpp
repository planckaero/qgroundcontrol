#include "PositionHistory.h"

PositionHistory::PositionHistory(int max_length, double min_distance_between_points, double min_seconds_between_points) :
    _max_length(max_length),
    _min_dist(min_distance_between_points),
    _min_secs(min_seconds_between_points)
{

}

void PositionHistory::push_position(QGeoPositionInfo position)
{
    if(_track_history.length() > 0)
    {
        //If this position is older than the latest position, reset the list
        auto latest_timestamp = _track_history.last().timestamp();
        if(position.timestamp() <= latest_timestamp)
        {
            _track_history.clear();
            _track_history.push_back(position);
        }
        else
        {
            //Verify that the new position isn't too soon
            if(_track_history.last().timestamp().secsTo(position.timestamp()) < _min_secs) return;

            //Verify that the position isn't too close
            if(_track_history.last().coordinate().distanceTo(position.coordinate()) < _min_dist) return;
        }
    }

    if(_track_history.length() >= _max_length)
    {
        _track_history.removeFirst();
    }
    _track_history.push_back(position);
}

QList <QGeoPositionInfo> PositionHistory::get_full_history()
{
    return _track_history;
}

QList<QGeoPositionInfo> PositionHistory::get_history_until(QDateTime oldest)
{

}

QList<QGeoPositionInfo> PositionHistory::get_history_until(double max_age_seconds)
{

}
