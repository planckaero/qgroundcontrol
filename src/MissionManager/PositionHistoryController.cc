#include "PositionHistoryController.h"
#include "QGCApplication.h"
#include "VisualMissionItem.h"

PositionHistoryController::PositionHistoryController(QObject* parent)
  : QObject(parent),
    _positionHistory(qgcApp()->toolbox()->positionHistory()),
    _missionController(nullptr),
    _altitude(30.0)
{ }


qreal PositionHistoryController::get_altitude()
{
  return _altitude;
}

void PositionHistoryController::set_altitude(double alt)
{
  _altitude = alt;
}

void PositionHistoryController::set_mission_controller(MissionController* controller)
{
  _missionController = controller;
}

void PositionHistoryController::send_mission()
{
  QList<QGeoPositionInfo> positions = _positionHistory->get_full_history();
  for(auto& pos : positions) {
    VisualMissionItem* item = _missionController->insertSimpleMissionItem(pos.coordinate(), -1);
    item->applyNewAltitude(_altitude);
  }
  _missionController->sendToVehicle();
}
