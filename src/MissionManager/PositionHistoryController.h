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

  void set_mission_controller(MissionController* controller);

  Q_INVOKABLE void send_mission();
private:
  PositionHistory* _positionHistory;
  MissionController* _missionController;
};
