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

  Q_PROPERTY(Fact* currentSpeed   READ get_current_speed   CONSTANT)
  Q_PROPERTY(Fact* currentHeading READ get_current_heading CONSTANT)
  Q_PROPERTY(Fact* windSpeed      READ get_wind_speed   CONSTANT)
  Q_PROPERTY(Fact* windHeading    READ get_wind_heading CONSTANT)

  void set_mission_controller(MissionController* controller);

  /// @brief Getters for mission parameters
  Fact* get_current_speed()   { return &_currentSpeed; }
  Fact* get_current_heading() { return &_currentHeading; }
  Fact* get_wind_speed()      { return &_windSpeed; }
  Fact* get_wind_heading()    { return &_windHeading; }

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
  Fact _currentSpeed;    /// Current speed in knots
  Fact _currentHeading;
  Fact _windSpeed;       /// Wind speed in knots
  Fact _windHeading;

  PositionHistory* _positionHistory;
  MissionController* _missionController;
};
