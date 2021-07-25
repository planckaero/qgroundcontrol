#include "PositionHistoryController.h"
#include "QGCApplication.h"
#include "SimpleMissionItem.h"

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

void PositionHistoryController::populate_survey_item(const QGeoCoordinate& takeoffCoord, const QList<QGeoPositionInfo>& posHist, SurveyComplexItem* survey)
{
  // Make one forward and backward path and merge after
  QList<QGeoCoordinate> fwdEnvelope, bwdEnvelope;

  // TODO: incorporate drift direction and speed
  QGeoCoordinate src_coord = takeoffCoord;
  qreal az_sum = 0.0; // used to calculate overall survey angle
  for(const auto& pos : posHist) {
    QGeoCoordinate cur_coord = pos.coordinate();
    qreal az = src_coord.azimuthTo(cur_coord);
    az_sum += az;
    // TODO: expand distance in a meaningful way. Maybe use drift direction and speed?
    fwdEnvelope.append(cur_coord.atDistanceAndAzimuth(_searchWidth, az-90.0));
    bwdEnvelope.append(cur_coord.atDistanceAndAzimuth(_searchWidth, az+90.0));
    src_coord = cur_coord;
  }

  std::reverse(bwdEnvelope.begin(), bwdEnvelope.end());
  fwdEnvelope.append(bwdEnvelope);

  survey->surveyAreaPolygon()->appendVertices(fwdEnvelope);
  // Average the azimuth angle across all track history points
  qreal survey_angle = az_sum/static_cast<qreal>(posHist.length());
  survey->setAzimuth(survey_angle);

  survey->cameraTriggerInTurnAround()->setRawValue(false);
  survey->hoverAndCapture()->setRawValue(false);
  survey->cameraCalc()->adjustedFootprintFrontal()->setRawValue(0);
}

void PositionHistoryController::send_mission(const QGeoCoordinate& takeoffCoord, double takeoffAlt)
{
  QList<QGeoPositionInfo> positions = _positionHistory->get_history_until(15*60); //15mins
  SimpleMissionItem* item = qobject_cast<SimpleMissionItem*>(_missionController->insertTakeoffItem(takeoffCoord, -1));
  item->missionItem().setParam1(takeoffAlt);
  std::reverse(positions.begin(), positions.end()); //reverse so we start at the most recent waypoint

  SurveyComplexItem* survey = qobject_cast<SurveyComplexItem*>(_missionController->insertComplexMissionItem(MissionController::patternSurveyName, takeoffCoord, -1));
  populate_survey_item(takeoffCoord, positions, survey);

  _missionController->insertLandItem(positions.back().coordinate(), -1);
  _missionController->sendToVehicle();
}
