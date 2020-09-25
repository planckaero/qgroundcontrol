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

  Q_INVOKABLE void send_mission(const QGeoCoordinate& takeoffCoord, double takeoffAlt);

signals:
  // Used to connect with flight map QML
  void newPositionAvailable(QGeoCoordinate pos);

private slots:
  // Takes position info and converts to coordinate object
  void convert_position_for_map(QGeoPositionInfo pos);

private:
  PositionHistory* _positionHistory;
  MissionController* _missionController;
};
