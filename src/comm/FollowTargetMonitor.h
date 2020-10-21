#pragma once

#include <atomic>
#include <QTimer>

#include "QGCToolbox.h"
#include "Vehicle.h"
#include <mavlink.h>

class LinkInterface;

class FollowTargetMonitor : public QGCTool {
    Q_OBJECT
public:
    FollowTargetMonitor(QGCApplication* app, QGCToolbox* toolbox);

    // Override from QGCTool
    virtual void setToolbox(QGCToolbox *toolbox);

    Q_PROPERTY(bool target_available READ get_target_health NOTIFY target_health_changed)
    Q_PROPERTY(QGeoCoordinate target_position READ get_target_position NOTIFY target_position_changed)

    // Get target health
    // @return  Health of follow target
    bool get_target_health();

    // Get latest target position
    // @return  Position of the latest follow target; this is a default constructed position prior to receiving any target
    QGeoCoordinate get_target_position();
signals:
    void target_health_changed();
    void target_position_changed(QGeoCoordinate pos);

public slots:
    void onMAVLinkMessage(LinkInterface* link, mavlink_message_t message);

private slots:
    void onTargetTimeout();
    void onActiveVehicleChanged(Vehicle* vehicle);

private:
    bool target_available;
    QTimer target_timer; //< Target health timeout
    std::atomic_int active_vehicle_sysid;
    QGeoCoordinate target_position;
};
