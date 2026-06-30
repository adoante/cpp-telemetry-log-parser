#pragma once

#include <unordered_map>
#include <vector>
#ifndef TELEMETRY_ANOMALY_H

#define TELEMETRY_ANOMALY_H

#include "ConfigParser.h"
#include "TelemetryData.h"

class TelemetryAnomaly {
private:
  TelemetryData data;

  // Configure ranges in configuration

  std::string TIMESTAMP;

  std::string MAX_TIMESTAMP;
  std::string MIN_TIMESTAMP;

  double MAX_LATITUDE;
  double MIN_LATITUDE;

  double MAX_LONGITUDE;
  double MIN_LONGITUDE;

  double MAX_IMU_ACC_X;
  double MIN_IMU_ACC_X;

  double MAX_IMU_ACC_Y;
  double MIN_IMU_ACC_Y;

  double MAX_IMU_ACC_Z;
  double MIN_IMU_ACC_Z;

  double MAX_IMU_GYRO_X;
  double MIN_IMU_GYRO_X;

  double MAX_IMU_GYRO_Y;
  double MIN_IMU_GYRO_Y;

  double MAX_IMU_GYRO_Z;
  double MIN_IMU_GYRO_Z;

  double MAX_LIDAR_DISTANCE;
  double MIN_LIDAR_DISTANCE;

  double MAX_SPEED;
  double MIN_SPEED;

  double MAX_WIND_SPEED;
  double MIN_WIND_SPEED;

  double MAX_BATTERY;
  double MIN_BATTERY;

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
  TelemetryAnomaly(TelemetryData data,
                   std::unordered_map<std::string, ConfigType>);

  void setTelemetryData(TelemetryData data);
  TelemetryData getTelemetryData() const;
  bool anomaly();
};

#endif // TELEMETRY_ANOMALY_H
