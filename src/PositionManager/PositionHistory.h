#pragma once
#include <QList>
#include <QtPositioning/qgeopositioninfosource.h>
#include <QMutex>
#include "QGCToolbox.h"

class PositionHistory : public QGCTool {
    Q_OBJECT

public:
    //Constructor
    PositionHistory(QGCApplication* app, QGCToolbox* toolbox);

    //Get the full history of positions
    QList<QGeoPositionInfo> get_full_history(void);

    //Get the history of positions until a certain time in the past or
    //maximum age in seconds
    QList<QGeoPositionInfo> get_history_until(QDateTime oldest);
    QList<QGeoPositionInfo> get_history_until(int max_age_seconds);

    //Clear the history
    void reset_history();

    //TODO: remove function after testing
    void populate_test_history();

    void setToolbox(QGCToolbox* toolbox) override;
signals:
    //Signal that a new position has been pushed
    void position_added(QGeoPositionInfo position);

private slots:
    //Push a new position into the queue
    void push_position(QGeoPositionInfo position);

private:
   QList<QGeoPositionInfo> _track_history;
   QMutex _track_history_mutex;
   int _max_length;
   double _min_dist;
   double _min_secs;
};
