#include "PositionHistoryController.h"
#include "QGCApplication.h"
#include "VisualMissionItem.h"

PositionHistoryController::PositionHistoryController(QObject* parent)
  : QObject(parent),
    _positionHistory(qgcApp()->toolbox()->positionHistory()),
    _missionController(nullptr)
{ }

void PositionHistoryController::set_mission_controller(MissionController* controller)
{
  _missionController = controller;
}

void PositionHistoryController::send_mission()
{
  QList<QGeoPositionInfo> positions = _positionHistory->get_full_history();
  for(auto& pos : positions) {
    _missionController->insertSimpleMissionItem(pos.coordinate(), -1);
  }
  _missionController->sendToVehicle();
}
