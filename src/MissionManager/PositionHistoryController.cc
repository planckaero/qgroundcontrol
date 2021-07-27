#include "PositionHistoryController.h"
#include "QGCApplication.h"
#include "SimpleMissionItem.h"

PositionHistoryController::PositionHistoryController(QObject* parent)
  : QObject(parent),
    _currentSpeed(0, "Current Speed", FactMetaData::valueTypeDouble),
    _currentHeading(0, "Current Heading", FactMetaData::valueTypeDouble),
    _windSpeed(0, "Wind Speed", FactMetaData::valueTypeDouble),
    _windHeading(0, "Wind Direction", FactMetaData::valueTypeDouble),
    _positionHistory(qgcApp()->toolbox()->positionHistory()),
    _missionController(nullptr)
{
  connect(_positionHistory, &PositionHistory::position_added, this, &PositionHistoryController::convert_position_for_map);
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

  _missionController->insertLandItem(positions.back().coordinate(), -1);
  _missionController->sendToVehicle();
}
