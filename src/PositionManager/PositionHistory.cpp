#include "PositionHistory.h"
#include "PositionManager.h"
#include "QGCApplication.h"
#include <QMutexLocker>

PositionHistory::PositionHistory(QGCApplication* app, QGCToolbox* toolbox)
    : QGCTool(app, toolbox),
      _max_length(100),
      _min_dist(50.),
      _min_secs(30)
{
}

void PositionHistory::setToolbox(QGCToolbox* toolbox)
{
    QGCTool::setToolbox(toolbox);
    connect(toolbox->qgcPositionManager(), &QGCPositionManager::positionInfoUpdated, this, &PositionHistory::push_position);
}

void PositionHistory::push_position(QGeoPositionInfo position)
{
    //Don't use bad data
    if(!position.isValid() ||
       (qAbs(position.coordinate().latitude()) <= 0.001 && qAbs(position.coordinate().longitude()) <= 0.001)) {
        return;
    }

    QMutexLocker lock(&_track_history_mutex);
    if(_track_history.length() > 0)
    {
        //If this position is older than the latest position, reset the list.
        //This should't be possible but the list is required to be chronologically
        //monotonically increasing
        auto latest_timestamp = _track_history.last().timestamp();
        if(position.timestamp() <= latest_timestamp)
        {
            _track_history.clear();
            _track_history.push_back(position);
        }
        else
        {
            //Verify that the new position isn't too soon
            if(latest_timestamp.secsTo(position.timestamp()) < _min_secs) return;

            //Verify that the position isn't too close
            if(_track_history.last().coordinate().distanceTo(position.coordinate()) < _min_dist) return;
        }
    }

    if(_track_history.length() >= _max_length)
    {
        _track_history.removeFirst();
    }
    _track_history.push_back(position);
    emit position_added(position);
}

QList <QGeoPositionInfo> PositionHistory::get_full_history()
{
    QMutexLocker lock(&_track_history_mutex);
    return _track_history;
}

QList<QGeoPositionInfo> PositionHistory::get_history_until(QDateTime oldest)
{
    QMutexLocker lock(&_track_history_mutex);
    QList<QGeoPositionInfo> ret;
    std::copy_if(_track_history.begin(),
                 _track_history.end(),
                 std::back_inserter(ret),
                 [oldest] (const QGeoPositionInfo& entry) -> bool {
                    return entry.timestamp() >= oldest;
                 });
    return ret;
}

QList<QGeoPositionInfo> PositionHistory::get_history_until(int max_age_seconds)
{
    return get_history_until(QDateTime::currentDateTime().addSecs(-max_age_seconds));
}

void PositionHistory::reset_history()
{
    QMutexLocker lock(&_track_history_mutex);
    _track_history.clear();
}
