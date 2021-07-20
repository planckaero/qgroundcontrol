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

  Q_PROPERTY(double currentSpeed   READ get_current_speed   WRITE set_current_speed)
  Q_PROPERTY(double currentHeading READ get_current_heading WRITE set_current_heading)
  Q_PROPERTY(double windSpeed      READ get_wind_speed   WRITE set_wind_speed)
  Q_PROPERTY(double windHeading    READ get_wind_heading WRITE set_wind_heading)

  void set_mission_controller(MissionController* controller);

  /// @brief Getters for speed and heading to modify mission
  double get_current_speed()   { return _currentSpeed; }
  double get_current_heading() { return _currentHeading; }
  double get_wind_speed()      { return _windSpeed; }
  double get_wind_heading()    { return _windHeading; }

  /// @brief Setters for speed and heading to modify mission
  void set_current_speed(double speed)     { _currentSpeed = speed; }
  void set_current_heading(double heading) { _currentHeading = heading; }
  void set_wind_speed(double speed)        { _windSpeed = speed; }
  void set_wind_heading(double heading)    { _windHeading = heading; }

  Q_INVOKABLE void send_mission(const QGeoCoordinate& takeoffCoord, double takeoffAlt);

signals:
  /// @brief Used to connect with flight map QML
  /// @param pos  coordinate of new position in history
  void newPositionAvailable(QGeoCoordinate pos);

private slots:
  /// @brief Takes position info and converts to coordinate object
  /// @param pos  position item to be converted to a coordinate
  void convert_position_for_map(QGeoPositionInfo pos);

private:
  double _currentSpeed = 0.0;
  double _currentHeading = 0.0;
  double _windSpeed = 0.0;
  double _windHeading = 0.0;

  PositionHistory* _positionHistory;
  MissionController* _missionController;

  QList<QGeoCoordinate> find_position_history_envelope(const QGeoCoordinate& takeoffCoord, const QList<QGeoPositionInfo>& posHist);
};
