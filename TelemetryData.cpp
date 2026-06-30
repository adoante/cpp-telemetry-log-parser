#include "TelemetryData.h"
#include <string>

TelemetryData::TelemetryData() {}

TelemetryData::TelemetryData(
    std::string timestamp, double latitude, double longitude, double altitude,
    double imu_acc_x, double imu_acc_y, double imu_acc_z, double imu_gyro_x,
    double imu_gyro_y, double imu_gyro_z, double lidar_distance, double speed,
    double wind_speed, double battery_level, bool obstacle_detected) {
  this->timestamp = timestamp;
  this->latitude = latitude;
  this->longitude = longitude;
  this->altitude = altitude;
  this->imu_acc_x = imu_acc_x;
  this->imu_acc_y = imu_acc_y;
  this->imu_acc_z = imu_acc_z;
  this->imu_gyro_x = imu_gyro_x;
  this->imu_gyro_y = imu_gyro_y;
  this->imu_gyro_z = imu_gyro_z;
  this->lidar_distance = lidar_distance;
  this->speed = speed;
  this->wind_speed = wind_speed;
  this->battery_level = battery_level;
  this->obstacle_detected = obstacle_detected;
}

std::string TelemetryData::getTimestamp() const { return timestamp; }
double TelemetryData::getLatitude() const { return latitude; }
double TelemetryData::getLongitude() const { return longitude; }
double TelemetryData::getAltitude() const { return altitude; }
double TelemetryData::getImu_acc_x() const { return imu_acc_x; }
double TelemetryData::getImu_acc_y() const { return imu_acc_y; }
double TelemetryData::getImu_acc_z() const { return imu_acc_z; }
double TelemetryData::getImu_gyro_x() const { return imu_gyro_x; }
double TelemetryData::getImu_gyro_y() const { return imu_gyro_y; }
double TelemetryData::getImu_gyro_z() const { return imu_gyro_z; }
double TelemetryData::getLidar_distance() const { return lidar_distance; }
double TelemetryData::getSpeed() const { return speed; }
double TelemetryData::getWind_speed() const { return wind_speed; }
double TelemetryData::getBattery_level() const { return battery_level; }
bool TelemetryData::getObstacle_detected() const { return obstacle_detected; };

std::ostream &operator<<(std::ostream &out, TelemetryData const &data) {
  out << data.timestamp + ", ";
  out << std::to_string(data.latitude) + ", ";
  out << std::to_string(data.longitude) + ", ";
  out << std::to_string(data.altitude) + ", ";
  out << std::to_string(data.imu_acc_x) + ", ";
  out << std::to_string(data.imu_acc_y) + ", ";
  out << std::to_string(data.imu_acc_z) + ", ";
  out << std::to_string(data.imu_gyro_x) + ", ";
  out << std::to_string(data.imu_gyro_y) + ", ";
  out << std::to_string(data.imu_gyro_z) + ", ";
  out << std::to_string(data.lidar_distance) + ", ";
  out << std::to_string(data.speed) + ", ";
  out << std::to_string(data.wind_speed) + ", ";
  out << std::to_string(data.battery_level) + ", ";
  out << std::to_string(data.obstacle_detected);

  return out;
}

std::string TelemetryData::to_string() const {
  std::ostringstream oss;
  oss << *this;
  return oss.str();
}
