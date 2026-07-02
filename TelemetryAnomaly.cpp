#include "TelemetryAnomaly.h"
#include "ConfigParser.h"
#include "TelemetryLogger.h"
#include <iomanip>
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
    anomalyLogger.log(LogLevel::WARNING, msg, false);
  }

  return result;
};

bool TelemetryAnomaly::anomalyLatitude() {
  bool result =
      data.getLatitude() >= MIN_LATITUDE and data.getLatitude() <= MAX_LATITUDE;

  if (!result) {
    anomalyLogger.log(LogLevel::INFO,
                      "Anomaly Detected: LATITUDE out of range. LATITUDE: " +
                          std::to_string(data.getLatitude()),
                      true);
  }

  return result;
};

bool TelemetryAnomaly::anomalyLongitude() {
  bool result = data.getLongitude() >= MIN_LONGITUDE &&
                data.getLongitude() <= MAX_LONGITUDE;

  if (!result) {
    anomalyLogger.log(LogLevel::INFO,
                      "Anomaly Detected: LONGITUDE out of range. LONGITUDE: " +
                          std::to_string(data.getLongitude()),
                      true);
  }

  return result;
}

bool TelemetryAnomaly::anomalyImu_acc_x() {
  bool result = data.getImu_acc_x() >= MIN_IMU_ACC_X &&
                data.getImu_acc_x() <= MAX_IMU_ACC_X;

  if (!result) {
    anomalyLogger.log(LogLevel::INFO,
                      "Anomaly Detected: IMU_ACC_X out of range. IMU_ACC_X: " +
                          std::to_string(data.getImu_acc_x()),
                      true);
  }

  return result;
}

bool TelemetryAnomaly::anomalyImu_acc_y() {
  bool result = data.getImu_acc_y() >= MIN_IMU_ACC_Y &&
                data.getImu_acc_y() <= MAX_IMU_ACC_Y;

  if (!result) {
    anomalyLogger.log(LogLevel::INFO,
                      "Anomaly Detected: IMU_ACC_Y out of range. IMU_ACC_Y: " +
                          std::to_string(data.getImu_acc_y()),
                      true);
  }

  return result;
}

bool TelemetryAnomaly::anomalyImu_acc_z() {
  bool result = data.getImu_acc_z() >= MIN_IMU_ACC_Z &&
                data.getImu_acc_z() <= MAX_IMU_ACC_Z;

  if (!result) {
    anomalyLogger.log(LogLevel::INFO,
                      "Anomaly Detected: IMU_ACC_Z out of range. IMU_ACC_Z: " +
                          std::to_string(data.getImu_acc_z()),
                      true);
  }

  return result;
}

bool TelemetryAnomaly::anomalyImu_gyro_x() {
  bool result = data.getImu_gyro_x() >= MIN_IMU_GYRO_X &&
                data.getImu_gyro_x() <= MAX_IMU_GYRO_X;

  if (!result) {
    anomalyLogger.log(
        LogLevel::INFO,
        "Anomaly Detected: IMU_GYRO_X out of range. IMU_GYRO_X: " +
            std::to_string(data.getImu_gyro_x()),
        true);
  }

  return result;
}

bool TelemetryAnomaly::anomalyImu_gyro_y() {
  bool result = data.getImu_gyro_y() >= MIN_IMU_GYRO_Y &&
                data.getImu_gyro_y() <= MAX_IMU_GYRO_Y;

  if (!result) {
    anomalyLogger.log(
        LogLevel::INFO,
        "Anomaly Detected: IMU_GYRO_Y out of range. IMU_GYRO_Y: " +
            std::to_string(data.getImu_gyro_y()),
        true);
  }

  return result;
}

bool TelemetryAnomaly::anomalyImu_gyro_z() {
  bool result = data.getImu_gyro_z() >= MIN_IMU_GYRO_Z &&
                data.getImu_gyro_z() <= MAX_IMU_GYRO_Z;

  if (!result) {
    anomalyLogger.log(
        LogLevel::INFO,
        "Anomaly Detected: IMU_GYRO_Z out of range. IMU_GYRO_Z: " +
            std::to_string(data.getImu_gyro_z()),
        true);
  }

  return result;
}

bool TelemetryAnomaly::anomalyLidar_distance() {
  bool result = data.getLidar_distance() >= MIN_LIDAR_DISTANCE &&
                data.getLidar_distance() <= MAX_LIDAR_DISTANCE;

  if (!result) {
    anomalyLogger.log(
        LogLevel::INFO,
        "Anomaly Detected: LIDAR_DISTANCE out of range. LIDAR_DISTANCE: " +
            std::to_string(data.getLidar_distance()),
        true);
  }

  return result;
}

bool TelemetryAnomaly::anomalySpeed() {
  bool result = data.getSpeed() >= MIN_SPEED && data.getSpeed() <= MAX_SPEED;

  if (!result) {
    anomalyLogger.log(LogLevel::INFO,
                      "Anomaly Detected: SPEED out of range. SPEED: " +
                          std::to_string(data.getSpeed()),
                      true);
  }

  return result;
}

bool TelemetryAnomaly::anomalyWind_speed() {
  bool result = data.getWind_speed() >= MIN_WIND_SPEED &&
                data.getWind_speed() <= MAX_WIND_SPEED;

  if (!result) {
    anomalyLogger.log(
        LogLevel::INFO,
        "Anomaly Detected: WIND_SPEED out of range. WIND_SPEED: " +
            std::to_string(data.getWind_speed()),
        true);
  }

  return result;
}

bool TelemetryAnomaly::anomalyBattery_level() {
  bool result = data.getBattery_level() >= MIN_BATTERY &&
                data.getBattery_level() <= MAX_BATTERY;

  if (!result) {
    anomalyLogger.log(
        LogLevel::INFO,
        "Anomaly Detected: BATTERY_LEVEL out of range. BATTERY_LEVEL: " +
            std::to_string(data.getBattery_level()),
        true);
  }

  return result;
}

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
