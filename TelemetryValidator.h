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
  const char *TIMESTAMP;

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

#endif // TELEMETRY_VALIDATOR_H
