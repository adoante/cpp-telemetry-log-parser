#pragma once

#ifndef TELEMETRY_VALIDATOR_H

#define TELEMETRY_VALIDATOR_H

#include "TelemetryData.h"

class TelemetryValidator {
private:
  TelemetryData data;

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
  bool validateObstacle_detected();

public:
  TelemetryValidator();
  TelemetryValidator(TelemetryData data);

  void setTelemetryData(TelemetryData data);
  TelemetryData getTelemetryData() const;
  bool validate();
};

#endif // TELEMETRY_VALIDATOR
