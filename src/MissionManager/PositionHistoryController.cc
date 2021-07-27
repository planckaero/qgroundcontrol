#include "PositionHistoryController.h"
#include "QGCApplication.h"
#include "SimpleMissionItem.h"

PositionHistoryController::PositionHistoryController(QObject* parent)
  : QObject(parent),
    _searchWidth(0, "Search Width", FactMetaData::valueTypeInt16),
    _currentSpeed(0, "Current Speed", FactMetaData::valueTypeDouble),
    _currentHeading(0, "Current Heading", FactMetaData::valueTypeDouble),
    _windSpeed(0, "Wind Speed", FactMetaData::valueTypeDouble),
    _windHeading(0, "Wind Direction", FactMetaData::valueTypeDouble),
    _positionHistory(qgcApp()->toolbox()->positionHistory()),
    _missionController(nullptr)
{
  connect(_positionHistory, &PositionHistory::position_added, this, &PositionHistoryController::convert_position_for_map);
  _searchWidth.setRawValue(0);
  _windSpeed.setRawValue(0);
  _windHeading.setRawValue(0);
  _currentSpeed.setRawValue(0);
  _currentHeading.setRawValue(0);

  _windSpeed.metaData()->setDecimalPlaces(1);
  _windHeading.metaData()->setDecimalPlaces(1);
  _currentSpeed.metaData()->setDecimalPlaces(1);
  _currentHeading.metaData()->setDecimalPlaces(1);
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
  // TODO: incorporate drift direction and speed
  // Create the survey polygon
  QList<QGeoCoordinate> fwdEnvelope, bwdEnvelope;

  QGeoCoordinate src_coord = takeoffCoord;
  qreal az_sum = 0.0; // used to calculate overall survey angle

  for(const auto& pos : posHist) {
    QGeoCoordinate cur_coord = pos.coordinate();
    qreal az = src_coord.azimuthTo(cur_coord);
    az_sum += az;
    // TODO: expand distance in a meaningful way. Maybe use drift direction and speed?
    fwdEnvelope.append(cur_coord.atDistanceAndAzimuth(_searchWidth.rawValue().toDouble(), az-90.0));
    bwdEnvelope.append(cur_coord.atDistanceAndAzimuth(_searchWidth.rawValue().toDouble(), az+90.0));
    src_coord = cur_coord;
  }

  std::reverse(bwdEnvelope.begin(), bwdEnvelope.end());
  fwdEnvelope.append(bwdEnvelope);
  survey->surveyAreaPolygon()->appendVertices(fwdEnvelope);

  // Grid spacing dictated by altitude
  // TODO: Parameterize footprint calculation
  qreal footprint = 1.2565*takeoffCoord.altitude() + 0.4634;
  survey->cameraCalc()->adjustedFootprintSide()->setRawValue(footprint*0.75); // 25% overlap

  // Average the azimuth angle across all track history points
  qreal survey_angle = az_sum/static_cast<qreal>(posHist.length());
  survey->setAzimuth(survey_angle);

  // Remove camera trigger distance waypoints from survey missioin
  survey->cameraTriggerInTurnAround()->setRawValue(false);
  survey->hoverAndCapture()->setRawValue(false);
  survey->cameraCalc()->adjustedFootprintFrontal()->setRawValue(0);
}

void PositionHistoryController::send_mission(const QGeoCoordinate& takeoffCoord, double takeoffAlt)
{
  // Check for previous takeoff items before resending
  if(_missionController->visualItems()->count() > 0) {
    for(int i = 0; i < _missionController->visualItems()->count(); ++i) {
      SimpleMissionItem* simple_item =  qobject_cast<SimpleMissionItem*>(_missionController->visualItems()->get(i));
      if(simple_item && simple_item->command() == MAV_CMD_NAV_PLANCK_TAKEOFF) {
          takeoffAlt = simple_item->missionItem().param1();
          break;
      }
    }
  }

   /// Remove previous mission
  _missionController->removeAll();

  QList<QGeoPositionInfo> positions = _positionHistory->get_history_until(15*60); //15mins
  SimpleMissionItem* item = qobject_cast<SimpleMissionItem*>(_missionController->insertTakeoffItem(takeoffCoord, -1));
  item->missionItem().setParam1(takeoffAlt);
  std::reverse(positions.begin(), positions.end()); //reverse so we start at the most recent waypoint

  /// Only search at path when search width is 0
  if(_searchWidth.rawValue().toDouble() == 0.0) {
    double wind_speed = _windSpeed.rawValue().toDouble();
    double wind_dir = _windHeading.rawValue().toDouble();
    double current_speed = _currentSpeed.rawValue().toDouble();
    double current_dir = _currentHeading.rawValue().toDouble();

    double init_msn_time = _missionController->missionTime();
    QDateTime curr_time = QDateTime::currentDateTime();
    for (const auto& pos : positions) {
      // Apply drift based on timing without mission transit time
      qint64 drift_t_s = pos.timestamp().secsTo(curr_time);
      qreal wind_drift  = 0.011 * (wind_speed*0.514444*static_cast<qreal>(drift_t_s)) + 0.07;
      qreal current_drift = current_speed*0.514444*static_cast<qreal>(drift_t_s);
      QGeoCoordinate drifted_coord = pos.coordinate().atDistanceAndAzimuth(wind_drift, wind_dir).atDistanceAndAzimuth(current_drift, current_dir);

      VisualMissionItem* wp = _missionController->insertSimpleMissionItem(drifted_coord, -1);

      // Update based on mission time
      double curr_msn_time = _missionController->missionTime();
      double mission_t_s = curr_msn_time - init_msn_time;
      wind_drift = 0.011 * (wind_speed*0.514444*static_cast<qreal>(mission_t_s)) + 0.07;
      current_drift = current_speed*0.514444*static_cast<qreal>(mission_t_s);
      wp->setCoordinate(drifted_coord.atDistanceAndAzimuth(wind_drift, wind_dir).atDistanceAndAzimuth(current_drift, current_dir));
      wp->applyNewAltitude(takeoffAlt);
    }
  }
  else {
    SurveyComplexItem* survey = qobject_cast<SurveyComplexItem*>(_missionController->insertComplexMissionItem(MissionController::patternSurveyName, takeoffCoord, -1));
    QGeoCoordinate takeoffCoordWithAlt(takeoffCoord.latitude(), takeoffCoord.longitude(), takeoffAlt);
    populate_survey_item(takeoffCoordWithAlt, positions, survey);
  }

  _missionController->insertLandItem(positions.back().coordinate(), -1);
  _missionController->sendToVehicle();
}
