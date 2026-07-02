#include "TelemetryValidator.h"
#include "ConfigParser.h"
#include "TelemetryLogger.h"

#include <iomanip>
#include <sstream>
#include <unordered_map>

std::filesystem::path valLogFile = "./validatorLogs.txt";
TelemetryLogger validatorLogger = TelemetryLogger(valLogFile);

TelemetryValidator::TelemetryValidator() {};

TelemetryValidator::TelemetryValidator(
    TelemetryData data, std::unordered_map<std::string, ConfigType> config) {
  this->data = data;

  TIMESTAMP = std::get<std::string>(config.at("TIMESTAMP"));

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

void TelemetryValidator::setTelemetryData(TelemetryData data) {
  this->data = data;
};

TelemetryData TelemetryValidator::getTelemetryData() const { return data; };

bool TelemetryValidator::validateTimestamp() {
  std::tm tm{};
  std::istringstream ss(data.getTimestamp());

  ss >> std::get_time(&tm, TIMESTAMP.c_str());

  bool result = !ss.fail() && ss.eof();

  if (!result) {
    std::string msg = "Invalid data: TIMESTAMP format incorrect. TIMESTAMP: " +
                      data.getTimestamp();
    validatorLogger.log(LogLevel::ERROR, msg, true);
  }

  return result;
};

bool TelemetryValidator::validateLatitude() {
  bool result =
      data.getLatitude() >= MIN_LATITUDE && data.getLatitude() <= MAX_LATITUDE;

  if (!result) {
    validatorLogger.log(LogLevel::ERROR,
                        "Validation Failed: LATITUDE out of range. LATITUDE: " +
                            std::to_string(data.getLatitude()),
                        true);
  }

  return result;
}

bool TelemetryValidator::validateLongitude() {
  bool result = data.getLongitude() >= MIN_LONGITUDE &&
                data.getLongitude() <= MAX_LONGITUDE;

  if (!result) {
    validatorLogger.log(
        LogLevel::ERROR,
        "Validation Failed: LONGITUDE out of range. LONGITUDE: " +
            std::to_string(data.getLongitude()),
        true);
  }

  return result;
}

bool TelemetryValidator::validateImu_acc_x() {
  bool result = data.getImu_acc_x() >= MIN_IMU_ACC_X &&
                data.getImu_acc_x() <= MAX_IMU_ACC_X;

  if (!result) {
    validatorLogger.log(
        LogLevel::ERROR,
        "Validation Failed: IMU_ACC_X out of range. IMU_ACC_X: " +
            std::to_string(data.getImu_acc_x()),
        true);
  }

  return result;
}

bool TelemetryValidator::validateImu_acc_y() {
  bool result = data.getImu_acc_y() >= MIN_IMU_ACC_Y &&
                data.getImu_acc_y() <= MAX_IMU_ACC_Y;

  if (!result) {
    validatorLogger.log(
        LogLevel::ERROR,
        "Validation Failed: IMU_ACC_Y out of range. IMU_ACC_Y: " +
            std::to_string(data.getImu_acc_y()),
        true);
  }

  return result;
}

bool TelemetryValidator::validateImu_acc_z() {
  bool result = data.getImu_acc_z() >= MIN_IMU_ACC_Z &&
                data.getImu_acc_z() <= MAX_IMU_ACC_Z;

  if (!result) {
    validatorLogger.log(
        LogLevel::ERROR,
        "Validation Failed: IMU_ACC_Z out of range. IMU_ACC_Z: " +
            std::to_string(data.getImu_acc_z()),
        true);
  }

  return result;
}

bool TelemetryValidator::validateImu_gyro_x() {
  bool result = data.getImu_gyro_x() >= MIN_IMU_GYRO_X &&
                data.getImu_gyro_x() <= MAX_IMU_GYRO_X;

  if (!result) {
    validatorLogger.log(
        LogLevel::ERROR,
        "Validation Failed: IMU_GYRO_X out of range. IMU_GYRO_X: " +
            std::to_string(data.getImu_gyro_x()),
        true);
  }

  return result;
}

bool TelemetryValidator::validateImu_gyro_y() {
  bool result = data.getImu_gyro_y() >= MIN_IMU_GYRO_Y &&
                data.getImu_gyro_y() <= MAX_IMU_GYRO_Y;

  if (!result) {
    validatorLogger.log(
        LogLevel::ERROR,
        "Validation Failed: IMU_GYRO_Y out of range. IMU_GYRO_Y: " +
            std::to_string(data.getImu_gyro_y()),
        true);
  }

  return result;
}

bool TelemetryValidator::validateImu_gyro_z() {
  bool result = data.getImu_gyro_z() >= MIN_IMU_GYRO_Z &&
                data.getImu_gyro_z() <= MAX_IMU_GYRO_Z;

  if (!result) {
    validatorLogger.log(
        LogLevel::ERROR,
        "Validation Failed: IMU_GYRO_Z out of range. IMU_GYRO_Z: " +
            std::to_string(data.getImu_gyro_z()),
        true);
  }

  return result;
}

bool TelemetryValidator::validateLidar_distance() {
  bool result = data.getLidar_distance() >= MIN_LIDAR_DISTANCE &&
                data.getLidar_distance() <= MAX_LIDAR_DISTANCE;

  if (!result) {
    validatorLogger.log(
        LogLevel::ERROR,
        "Validation Failed: LIDAR_DISTANCE out of range. LIDAR_DISTANCE: " +
            std::to_string(data.getLidar_distance()),
        true);
  }

  return result;
}

bool TelemetryValidator::validateSpeed() {
  bool result = data.getSpeed() >= MIN_SPEED && data.getSpeed() <= MAX_SPEED;

  if (!result) {
    validatorLogger.log(LogLevel::ERROR,
                        "Validation Failed: SPEED out of range. SPEED: " +
                            std::to_string(data.getSpeed()),
                        true);
  }

  return result;
}

bool TelemetryValidator::validateWind_speed() {
  bool result = data.getWind_speed() >= MIN_WIND_SPEED &&
                data.getWind_speed() <= MAX_WIND_SPEED;

  if (!result) {
    validatorLogger.log(
        LogLevel::ERROR,
        "Validation Failed: WIND_SPEED out of range. WIND_SPEED: " +
            std::to_string(data.getWind_speed()),
        true);
  }

  return result;
}

bool TelemetryValidator::validateBattery_level() {
  bool result = data.getBattery_level() >= MIN_BATTERY &&
                data.getBattery_level() <= MAX_BATTERY;

  if (!result) {
    validatorLogger.log(
        LogLevel::ERROR,
        "Validation Failed: BATTERY_LEVEL out of range. BATTERY_LEVEL: " +
            std::to_string(data.getBattery_level()),
        true);
  }

  return result;
}

bool TelemetryValidator::validate() {
  bool result = true;

  result = result &= validateTimestamp();
  result = result &= validateLatitude();
  result = result &= validateLongitude();
  result = result &= validateImu_acc_x();
  result = result &= validateImu_acc_y();
  result = result &= validateImu_acc_z();
  result = result &= validateImu_gyro_x();
  result = result &= validateImu_gyro_y();
  result = result &= validateImu_gyro_z();
  result = result &= validateLidar_distance();
  result = result &= validateSpeed();
  result = result &= validateWind_speed();
  result = result &= validateBattery_level();

  return result;
};
