#ifndef PLANCKLISTENER_H
#define PLANCKLISTENER_H

#include <QObject>
#include <QTimer>
#include "QGCToolbox.h"
#include <mavlink.h>

class LinkInterface;

class PlanckListener : public QGCTool
{
    Q_OBJECT
public:
    PlanckListener(QGCApplication* app, QGCToolbox* toolbox);

    // Override from QGCTool
    virtual void setToolbox(QGCToolbox *toolbox);
    Q_PROPERTY(bool TagHealth  READ TagHealth  NOTIFY HealthChanged)
    Q_PROPERTY(bool BoatHealth READ BoatHealth  NOTIFY HealthChanged)

    bool TagHealth() { return tag_health; }
    bool BoatHealth() { return boat_health; }
signals:
    void HealthChanged();

public slots:
    void onMAVLinkMessage(LinkInterface* link, mavlink_message_t message);
    void onHealthTimeout();

private:
    QTimer health_timer;
    bool tag_health;
    bool boat_health;
};

#endif // PLANCKLISTENER_H
