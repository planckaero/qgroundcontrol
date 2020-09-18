#include "PositionHistoryController.h"
#include "QGCApplication.h"
#include "SimpleMissionItem.h"

PositionHistoryController::PositionHistoryController(QObject* parent)
  : QObject(parent),
    _positionHistory(qgcApp()->toolbox()->positionHistory()),
    _missionController(nullptr)
{ }

void PositionHistoryController::set_mission_controller(MissionController* controller)
{
  _missionController = controller;
}

void PositionHistoryController::send_mission(const QGeoCoordinate& takeoffCoord, double takeoffAlt)
{
  QList<QGeoPositionInfo> positions = _positionHistory->get_full_history();
  SimpleMissionItem* item = qobject_cast<SimpleMissionItem*>(_missionController->insertTakeoffItem(takeoffCoord, -1));
  item->missionItem().setParam1(takeoffAlt);
  for(auto& pos : positions) {
    _missionController->insertSimpleMissionItem(pos.coordinate(), -1);
  }
  _missionController->insertLandItem(positions.back().coordinate(), -1);
  _missionController->sendToVehicle();
}
