#pragma once

#include "PlanCreator.h"
#include "MissionController.h"
#include "PositionHistory.h"
#include "SurveyComplexItem.h"

/// Interface between PositionHistory and QML element
class PositionHistoryController : public QObject
{
  Q_OBJECT

public:
  PositionHistoryController(QObject* parent = nullptr);

  Q_PROPERTY(MissionController* missionController WRITE set_mission_controller)

  Q_PROPERTY(qreal searchWidth    READ get_search_width    WRITE set_search_width)
  Q_PROPERTY(qreal currentSpeed   READ get_current_speed   WRITE set_current_speed)
  Q_PROPERTY(qreal currentHeading READ get_current_heading WRITE set_current_heading)
  Q_PROPERTY(qreal windSpeed      READ get_wind_speed   WRITE set_wind_speed)
  Q_PROPERTY(qreal windHeading    READ get_wind_heading WRITE set_wind_heading)

  void set_mission_controller(MissionController* controller);

  /// @brief Getters for mission parameters
  qreal get_search_width()    { return _searchWidth; }
  qreal get_current_speed()   { return _currentSpeed; }
  qreal get_current_heading() { return _currentHeading; }
  qreal get_wind_speed()      { return _windSpeed; }
  qreal get_wind_heading()    { return _windHeading; }

  /// @brief Setters for mission parameters
  void set_search_width(qreal width)      { _searchWidth = width; }
  void set_current_speed(qreal speed)     { _currentSpeed = speed; }
  void set_current_heading(qreal heading) { _currentHeading = heading; }
  void set_wind_speed(qreal speed)        { _windSpeed = speed; }
  void set_wind_heading(qreal heading)    { _windHeading = heading; }

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
  qreal _searchWidth = 10.0; /// Width in meters to fly in search pattern
  qreal _currentSpeed = 0.0;
  qreal _currentHeading = 0.0;
  qreal _windSpeed = 0.0;
  qreal _windHeading = 0.0;

  PositionHistory* _positionHistory;
  MissionController* _missionController;

  void populate_survey_item(const QGeoCoordinate& takeoffCoord, const QList<QGeoPositionInfo>& posHist, SurveyComplexItem* survey);
};
