#include "TelemetryAnomaly.h"
#include <iomanip>
#include <sstream>

TelemetryAnomaly::TelemetryAnomaly() {};

TelemetryAnomaly::TelemetryAnomaly(TelemetryData data) { this->data = data; };

void TelemetryAnomaly::setTelemetryData(TelemetryData data) {
  this->data = data;
};

TelemetryData TelemetryAnomaly::getTelemetryData() const { return data; };

bool TelemetryAnomaly::anomalyTimestamp() {
  std::tm tm{};
  std::istringstream ss(data.getTimestamp());

  ss >> std::get_time(&tm, TIMESTAMP);

  return !ss.fail() && ss.eof();
};

bool TelemetryAnomaly::anomalyLatitude() {
  return data.getLatitude() >= MIN_LATITUDE and
         data.getLatitude() <= MAX_LATITUDE;
};

bool TelemetryAnomaly::anomalyLongitude() {
  return data.getLongitude() >= MIN_LONGITUDE and
         data.getLongitude() <= MAX_LONGITUDE;
};

bool TelemetryAnomaly::anomalyImu_acc_x() {
  return data.getImu_acc_x() >= MIN_IMU_ACC_X and
         data.getImu_acc_x() <= MAX_IMU_ACC_X;
};

bool TelemetryAnomaly::anomalyImu_acc_y() {
  return data.getImu_acc_y() >= MIN_IMU_ACC_Y and
         data.getImu_acc_y() <= MAX_IMU_ACC_Y;
};

bool TelemetryAnomaly::anomalyImu_acc_z() {
  return data.getImu_acc_z() >= MIN_IMU_ACC_Z and
         data.getImu_acc_z() <= MAX_IMU_ACC_Z;
};

bool TelemetryAnomaly::anomalyImu_gyro_x() {
  return data.getImu_gyro_x() >= MIN_IMU_GYRO_X and
         data.getImu_gyro_x() <= MAX_IMU_GYRO_X;
};

bool TelemetryAnomaly::anomalyImu_gyro_y() {
  return data.getImu_gyro_y() >= MIN_IMU_GYRO_Y and
         data.getImu_gyro_y() <= MAX_IMU_GYRO_Y;
};

bool TelemetryAnomaly::anomalyImu_gyro_z() {
  return data.getImu_gyro_z() >= MIN_IMU_GYRO_Z and
         data.getImu_gyro_z() <= MAX_IMU_GYRO_Z;
};

bool TelemetryAnomaly::anomalyLidar_distance() {
  return data.getLidar_distance() >= MIN_LIDAR_DISTANCE and
         data.getLidar_distance() <= MAX_LIDAR_DISTANCE;
};

bool TelemetryAnomaly::anomalySpeed() {
  return data.getSpeed() >= MIN_SPEED and data.getSpeed() <= MAX_SPEED;
};

bool TelemetryAnomaly::anomalyWind_speed() {
  return data.getWind_speed() >= MIN_WIND_SPEED and
         data.getWind_speed() <= MAX_WIND_SPEED;
};

bool TelemetryAnomaly::anomalyBattery_level() {
  return data.getBattery_level() <= MAX_BATTERY and
         data.getBattery_level() >= MIN_BATTERY;
};

bool TelemetryAnomaly::anomaly() {
  bool result = true;

  result = result && anomalyTimestamp();
  result = result && anomalyLatitude();
  result = result && anomalyLongitude();
  result = result && anomalyImu_acc_x();
  result = result && anomalyImu_acc_y();
  result = result && anomalyImu_acc_z();
  result = result && anomalyImu_gyro_x();
  result = result && anomalyImu_gyro_y();
  result = result && anomalyImu_gyro_z();
  result = result && anomalyLidar_distance();
  result = result && anomalySpeed();
  result = result && anomalyWind_speed();
  result = result && anomalyBattery_level();

  return result;
};
