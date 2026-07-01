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
  return data.getLatitude() >= MIN_LATITUDE and
         data.getLatitude() <= MAX_LATITUDE;
};

bool TelemetryValidator::validateLongitude() {
  return data.getLongitude() >= MIN_LONGITUDE and
         data.getLongitude() <= MAX_LONGITUDE;
};

bool TelemetryValidator::validateImu_acc_x() {
  return data.getImu_acc_x() >= MIN_IMU_ACC_X and
         data.getImu_acc_x() <= MAX_IMU_ACC_X;
};

bool TelemetryValidator::validateImu_acc_y() {
  return data.getImu_acc_y() >= MIN_IMU_ACC_Y and
         data.getImu_acc_y() <= MAX_IMU_ACC_Y;
};

bool TelemetryValidator::validateImu_acc_z() {
  return data.getImu_acc_z() >= MIN_IMU_ACC_Z and
         data.getImu_acc_z() <= MAX_IMU_ACC_Z;
};

bool TelemetryValidator::validateImu_gyro_x() {
  return data.getImu_gyro_x() >= MIN_IMU_GYRO_X and
         data.getImu_gyro_x() <= MAX_IMU_GYRO_X;
};

bool TelemetryValidator::validateImu_gyro_y() {
  return data.getImu_gyro_y() >= MIN_IMU_GYRO_Y and
         data.getImu_gyro_y() <= MAX_IMU_GYRO_Y;
};

bool TelemetryValidator::validateImu_gyro_z() {
  return data.getImu_gyro_z() >= MIN_IMU_GYRO_Z and
         data.getImu_gyro_z() <= MAX_IMU_GYRO_Z;
};

bool TelemetryValidator::validateLidar_distance() {
  return data.getLidar_distance() >= MIN_LIDAR_DISTANCE and
         data.getLidar_distance() <= MAX_LIDAR_DISTANCE;
};

bool TelemetryValidator::validateSpeed() {
  return data.getSpeed() >= MIN_SPEED and data.getSpeed() <= MAX_SPEED;
};

bool TelemetryValidator::validateWind_speed() {
  return data.getWind_speed() >= MIN_WIND_SPEED and
         data.getWind_speed() <= MAX_WIND_SPEED;
};

bool TelemetryValidator::validateBattery_level() {
  return data.getBattery_level() <= MAX_BATTERY and
         data.getBattery_level() >= MIN_BATTERY;
};

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
