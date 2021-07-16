#include "PositionHistoryController.h"
#include "QGCApplication.h"
#include "SimpleMissionItem.h"
#include "SurveyComplexItem.h"

PositionHistoryController::PositionHistoryController(QObject* parent)
  : QObject(parent),
    _positionHistory(qgcApp()->toolbox()->positionHistory()),
    _missionController(nullptr)
{
    connect(_positionHistory, &PositionHistory::position_added, this, &PositionHistoryController::convert_position_for_map);
}

void PositionHistoryController::convert_position_for_map(QGeoPositionInfo pos)
{
    emit newPositionAvailable(pos.coordinate());
}

void PositionHistoryController::set_mission_controller(MissionController* controller)
{
  _missionController = controller;
}

void PositionHistoryController::send_mission(const QGeoCoordinate& takeoffCoord, double takeoffAlt)
{
  QList<QGeoPositionInfo> positions = _positionHistory->get_history_until(15*60); //15mins
  SimpleMissionItem* item = qobject_cast<SimpleMissionItem*>(_missionController->insertTakeoffItem(takeoffCoord, -1));
  item->missionItem().setParam1(takeoffAlt);
  std::reverse(positions.begin(), positions.end()); //reverse so we start at the most recent waypoint

  SurveyComplexItem* survey = qobject_cast<SurveyComplexItem*>(_missionController->insertComplexMissionItem(MissionController::patternSurveyName, takeoffCoord, -1));
  {
    // TODO: placeholder until polygon strategy developed (incorporate drift speed and direction)
    QList<QGeoCoordinate> coords;
    coords.append(takeoffCoord);
    for(const auto& pos : positions)
        coords.append(pos.coordinate());
    survey->surveyAreaPolygon()->setPath(coords);
    // TODO: change angle to point away from takeoff point
    // 0 angle points path towards East
  }

  _missionController->insertLandItem(positions.back().coordinate(), -1);
  _missionController->sendToVehicle();
}
