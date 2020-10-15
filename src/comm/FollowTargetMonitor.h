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

    Q_PROPERTY(bool target_available READ get_target_status NOTIFY target_status_changed)

    bool get_target_status();
signals:
    void target_status_changed();

public slots:
    void onMAVLinkMessage(LinkInterface* link, mavlink_message_t message);

private slots:
    void onTargetTimeout();
    void onActiveVehicleChanged(Vehicle* vehicle);

private:
    bool target_available;
    QTimer target_timer;
    std::atomic_int active_vehicle_sysid;
};
