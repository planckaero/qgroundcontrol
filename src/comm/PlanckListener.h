#ifndef PLANCKLISTENER_H
#define PLANCKLISTENER_H

#include <QObject>
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
    Q_PROPERTY(bool tagHealth  READ tagHealth  NOTIFY tagHealthChanged)
    Q_PROPERTY(bool boatHealth READ boatHealth  NOTIFY boatHealthChanged)

    bool tagHealth() { return _tagHealth; }
    bool boatHealth() { return _boatHealth; }
signals:
    void landingPadPosition(int lat, int lon);
    void status(bool tag_est_ok, bool boat_est_ok);
    void boatHealthChanged(bool);
    void tagHealthChanged(bool);

public slots:
    void onMAVLinkMessage(LinkInterface* link, mavlink_message_t message);

private:
    bool _tagHealth;
    bool _boatHealth;
};

#endif // PLANCKLISTENER_H
