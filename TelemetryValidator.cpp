#include "TelemetryValidator.h"
#include <iomanip>
#include <sstream>

TelemetryValidator::TelemetryValidator() {};

TelemetryValidator::TelemetryValidator(TelemetryData data) {
  this->data = data;
};

void TelemetryValidator::setTelemetryData(TelemetryData data) {
  this->data = data;
};

TelemetryData TelemetryValidator::getTelemetryData() const { return data; };

bool TelemetryValidator::validateTimestamp() {
  std::tm tm{};
  std::istringstream ss(data.getTimestamp());

  ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");

  return !ss.fail() && ss.eof();
};

bool TelemetryValidator::validateLatitude() {
  return data.getLatitude() < 90.0 or data.getLatitude() > -90.0;
};

bool TelemetryValidator::validateLongitude() {
  return data.getLongitude() < 180.0 or data.getLongitude() > -180.0;
};

bool TelemetryValidator::validateImu_acc_x() { return true; };
bool TelemetryValidator::validateImu_acc_y() { return true; };
bool TelemetryValidator::validateImu_acc_z() { return true; };
bool TelemetryValidator::validateImu_gyro_x() { return true; };
bool TelemetryValidator::validateImu_gyro_y() { return true; };
bool TelemetryValidator::validateImu_gyro_z() { return true; };
bool TelemetryValidator::validateLidar_distance() { return true; };
bool TelemetryValidator::validateSpeed() { return true; };
bool TelemetryValidator::validateWind_speed() { return true; };
bool TelemetryValidator::validateBattery_level() { return true; };
bool TelemetryValidator::validateObstacle_detected() { return true; };

bool TelemetryValidator::validate() {
  bool result = true;

  result = result && validateTimestamp();
  result = result && validateLatitude();
  result = result && validateLongitude();
  result = result && validateImu_acc_x();
  result = result && validateImu_acc_y();
  result = result && validateImu_acc_z();
  result = result && validateImu_gyro_x();
  result = result && validateImu_gyro_y();
  result = result && validateImu_gyro_z();
  result = result && validateLidar_distance();
  result = result && validateSpeed();
  result = result && validateWind_speed();
  result = result && validateBattery_level();
  result = result && validateObstacle_detected();

  return result;
};
