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

QList<QGeoCoordinate> PositionHistoryController::find_position_history_envelope(const QGeoCoordinate& takeoffCoord, const QList<QGeoPositionInfo>& posHist)
{
  // Make one forward and backward path and merge after
  QList<QGeoCoordinate> fwdEnvelope, bwdEnvelope;

  // TODO: incorporate drift direction and speed
  QGeoCoordinate src_coord = takeoffCoord;
  qreal spread = 5.0;
  for(const auto& pos : posHist) {
    QGeoCoordinate cur_coord = pos.coordinate();
    qreal az = src_coord.azimuthTo(cur_coord);
    // TODO: expand distance in a meaningful way. Maybe use drift direction and speed?
    fwdEnvelope.append(cur_coord.atDistanceAndAzimuth(spread, az-90.0));
    bwdEnvelope.append(cur_coord.atDistanceAndAzimuth(spread, az+90.0));
    spread += 5;
    src_coord = cur_coord;
  }

  std::reverse(bwdEnvelope.begin(), bwdEnvelope.end());
  fwdEnvelope.append(bwdEnvelope);
  return fwdEnvelope;
}

void PositionHistoryController::send_mission(const QGeoCoordinate& takeoffCoord, double takeoffAlt)
{
  QList<QGeoPositionInfo> positions = _positionHistory->get_history_until(15*60); //15mins
  SimpleMissionItem* item = qobject_cast<SimpleMissionItem*>(_missionController->insertTakeoffItem(takeoffCoord, -1));
  item->missionItem().setParam1(takeoffAlt);
  std::reverse(positions.begin(), positions.end()); //reverse so we start at the most recent waypoint

  SurveyComplexItem* survey = qobject_cast<SurveyComplexItem*>(_missionController->insertComplexMissionItem(MissionController::patternSurveyName, takeoffCoord, -1));
  survey->surveyAreaPolygon()->appendVertices(find_position_history_envelope(takeoffCoord, positions));

  _missionController->insertLandItem(positions.back().coordinate(), -1);
  _missionController->sendToVehicle();
}
