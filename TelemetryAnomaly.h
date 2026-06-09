#pragma once

#ifndef TELEMETRY_ANOMALY_H

#define TELEMETRY_ANOMALY_H

#include "TelemetryData.h"

class TelemetryAnomaly {
private:
  TelemetryData data;

  // Configure ranges in configuration

  // std::get_time requires const char*
  const char *TIMESTAMP = "%Y-%m-%d %H:%M:%S";

  double MAX_LATITUDE = 90.0;
  double MIN_LATITUDE = -90.0;

  double MAX_LONGITUDE = 180.0;
  double MIN_LONGITUDE = -180.0;

  double MAX_IMU_ACC_X = 20.0;
  double MIN_IMU_ACC_X = -20.0;

  double MAX_IMU_ACC_Y = 20.0;
  double MIN_IMU_ACC_Y = -20.0;

  double MAX_IMU_ACC_Z = 20.0;
  double MIN_IMU_ACC_Z = -20.0;

  double MAX_IMU_GYRO_X = 500.0;
  double MIN_IMU_GYRO_X = -500.0;

  double MAX_IMU_GYRO_Y = 500.0;
  double MIN_IMU_GYRO_Y = -500.0;

  double MAX_IMU_GYRO_Z = 500.0;
  double MIN_IMU_GYRO_Z = -500.0;

  double MAX_LIDAR_DISTANCE = 200.0;
  double MIN_LIDAR_DISTANCE = 0.1;

  double MAX_SPEED = 100.0;
  double MIN_SPEED = 0.0;

  double MAX_WIND_SPEED = 60.0;
  double MIN_WIND_SPEED = 0.0;

  double MAX_BATTERY = 100.0;
  double MIN_BATTERY = 0.0;

  bool anomalyTimestamp();
  bool anomalyLatitude();
  bool anomalyLongitude();
  bool anomalyImu_acc_x();
  bool anomalyImu_acc_y();
  bool anomalyImu_acc_z();
  bool anomalyImu_gyro_x();
  bool anomalyImu_gyro_y();
  bool anomalyImu_gyro_z();
  bool anomalyLidar_distance();
  bool anomalySpeed();
  bool anomalyWind_speed();
  bool anomalyBattery_level();

public:
  TelemetryAnomaly();
  TelemetryAnomaly(TelemetryData data);

  void setTelemetryData(TelemetryData data);
  TelemetryData getTelemetryData() const;
  bool anomaly();
};

#endif // TELEMETRY_ANOMALY_H
