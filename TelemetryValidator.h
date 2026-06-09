#pragma once

#ifndef TELEMETRY_VALIDATOR_H

#define TELEMETRY_VALIDATOR_H

#include "TelemetryData.h"

class TelemetryValidator {
private:
  TelemetryData data;

  // Valid Ranges are dependent on UAV
  // Configure ranges in configuration file

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

  bool validateTimestamp();
  bool validateLatitude();
  bool validateLongitude();
  bool validateImu_acc_x();
  bool validateImu_acc_y();
  bool validateImu_acc_z();
  bool validateImu_gyro_x();
  bool validateImu_gyro_y();
  bool validateImu_gyro_z();
  bool validateLidar_distance();
  bool validateSpeed();
  bool validateWind_speed();
  bool validateBattery_level();

public:
  TelemetryValidator();
  TelemetryValidator(TelemetryData data);

  void setTelemetryData(TelemetryData data);
  TelemetryData getTelemetryData() const;
  bool validate();
};

#endif // TELEMETRY_VALIDATOR
