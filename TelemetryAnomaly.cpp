#include "TelemetryAnomaly.h"
#include "ConfigParser.h"
#include "TelemetryLogger.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <unordered_map>

std::filesystem::path anomalyLogFile = "./AnomalyLogs.txt";
TelemetryLogger anomalyLogger = TelemetryLogger(anomalyLogFile);

TelemetryAnomaly::TelemetryAnomaly() {};

TelemetryAnomaly::TelemetryAnomaly(
    TelemetryData data, std::unordered_map<std::string, ConfigType> config) {
  this->data = data;

  TIMESTAMP = std::get<std::string>(config.at("TIMESTAMP"));

  MAX_TIMESTAMP = std::get<std::string>(config.at("MAX_TIMESTAMP"));
  MIN_TIMESTAMP = std::get<std::string>(config.at("MIN_TIMESTAMP"));

  MAX_LATITUDE = std::get<double>(config.at("MAX_LATITUDE"));
  MIN_LATITUDE = std::get<double>(config.at("MIN_LATITUDE"));

  MAX_LONGITUDE = std::get<double>(config.at("MAX_LONGITUDE"));
  MIN_LONGITUDE = std::get<double>(config.at("MIN_LONGITUDE"));

  MAX_IMU_ACC_X = std::get<double>(config.at("MAX_IMU_ACC_X"));
  MIN_IMU_ACC_X = std::get<double>(config.at("MIN_IMU_ACC_X"));

  MAX_IMU_ACC_Y = std::get<double>(config.at("MAX_IMU_ACC_Y"));
  MIN_IMU_ACC_Y = std::get<double>(config.at("MIN_IMU_ACC_Y"));

  MAX_IMU_ACC_Z = std::get<double>(config.at("MAX_IMU_ACC_Z"));
  MIN_IMU_ACC_Z = std::get<double>(config.at("MIN_IMU_ACC_Z"));

  MAX_IMU_GYRO_X = std::get<double>(config.at("MAX_IMU_GYRO_X"));
  MIN_IMU_GYRO_X = std::get<double>(config.at("MIN_IMU_GYRO_X"));

  MAX_IMU_GYRO_Y = std::get<double>(config.at("MAX_IMU_GYRO_Y"));
  MIN_IMU_GYRO_Y = std::get<double>(config.at("MIN_IMU_GYRO_Y"));

  MAX_IMU_GYRO_Z = std::get<double>(config.at("MAX_IMU_GYRO_Z"));
  MIN_IMU_GYRO_Z = std::get<double>(config.at("MIN_IMU_GYRO_Z"));

  MAX_LIDAR_DISTANCE = std::get<double>(config.at("MAX_LIDAR_DISTANCE"));
  MIN_LIDAR_DISTANCE = std::get<double>(config.at("MIN_LIDAR_DISTANCE"));

  MAX_SPEED = std::get<double>(config.at("MAX_SPEED"));
  MIN_SPEED = std::get<double>(config.at("MIN_SPEED"));

  MAX_WIND_SPEED = std::get<double>(config.at("MAX_WIND_SPEED"));
  MIN_WIND_SPEED = std::get<double>(config.at("MIN_WIND_SPEED"));

  MAX_BATTERY = std::get<double>(config.at("MAX_BATTERY"));
  MIN_BATTERY = std::get<double>(config.at("MIN_BATTERY"));
};

void TelemetryAnomaly::setTelemetryData(TelemetryData data) {
  this->data = data;
};

TelemetryData TelemetryAnomaly::getTelemetryData() const { return data; };

bool TelemetryAnomaly::anomalyTimestamp() {
  std::tm data_tm{};
  std::tm min_tm{};
  std::tm max_tm{};

  std::istringstream(data.getTimestamp()) >>
      std::get_time(&data_tm, TIMESTAMP.c_str());
  std::istringstream(MIN_TIMESTAMP) >>
      std::get_time(&min_tm, TIMESTAMP.c_str());
  std::istringstream(MAX_TIMESTAMP) >>
      std::get_time(&max_tm, TIMESTAMP.c_str());

  std::time_t data_time = std::mktime(&data_tm);
  std::time_t min_time = std::mktime(&min_tm);
  std::time_t max_time = std::mktime(&max_tm);

  bool result = data_time >= min_time && data_time <= max_time;

  if (!result) {
    std::string msg = "Anomaly Detected: TIMESTAMP out of range. TIMESTAMP: " +
                      data.getTimestamp();
    anomalyLogger.log(LogLevel::WARNING, msg, true);
  }

  return result;
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

  result = result &= anomalyTimestamp();
  result = result &= anomalyLatitude();
  result = result &= anomalyLongitude();
  result = result &= anomalyImu_acc_x();
  result = result &= anomalyImu_acc_y();
  result = result &= anomalyImu_acc_z();
  result = result &= anomalyImu_gyro_x();
  result = result &= anomalyImu_gyro_y();
  result = result &= anomalyImu_gyro_z();
  result = result &= anomalyLidar_distance();
  result = result &= anomalySpeed();
  result = result &= anomalyWind_speed();
  result = result &= anomalyBattery_level();

  std::string msg = "No anomalies detected in [" + data.to_string() + "]";

  if (result) {
    anomalyLogger.log(LogLevel::INFO, msg, false);
  }

  return result;
};
