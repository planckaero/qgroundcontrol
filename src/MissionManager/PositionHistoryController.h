#pragma once

#include "PlanCreator.h"
#include "MissionController.h"
#include "PositionHistory.h"

/// Interface between PositionHistory and QML element
class PositionHistoryController : public QObject
{
  Q_OBJECT

public:
  PositionHistoryController(QObject* parent = nullptr);

  Q_PROPERTY(MissionController* missionController WRITE set_mission_controller)
  Q_PROPERTY(qreal altitude READ get_altitude WRITE set_altitude)

  qreal get_altitude();

  /// Set a fixed altitude that all position history points that should be set to
  /// @param alt  altitude in msl to set
  void set_altitude(double alt);

  void set_mission_controller(MissionController* controller);

  Q_INVOKABLE void send_mission();
private:
  PositionHistory* _positionHistory;
  MissionController* _missionController;
  qreal _altitude;
};
