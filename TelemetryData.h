#pragma once

#ifndef TELEMETRY_DATA_H
#define TELEMETRY_DATA_H

#include <filesystem>
#include <string>

class TelemetryData {
private:
  std::string timestamp;
  double latitude;
  double longitude;
  double altitude;
  double imu_acc_x;
  double imu_acc_y;
  double imu_acc_z;
  double imu_gyro_x;
  double imu_gyro_y;
  double imu_gyro_z;
  double lidar_distance;
  double speed;
  double wind_speed;
  double battery_level;
  bool obstacle_detected;

public:
  TelemetryData();
  TelemetryData(std::string timestamp, double latitude, double longitude,
                double altitude, double imu_acc_x, double imu_acc_y,
                double imu_acc_z, double imu_gyro_x, double imu_gyro_y,
                double imu_gyro_z, double lidar_distance, double speed,
                double wind_speed, double battery_level,
                bool obstacle_detected);

  std::string getTimestamp() const;
  double getLatitude() const;
  double getLongitude() const;
  double getAltitude() const;
  double getImu_acc_x() const;
  double getImu_acc_y() const;
  double getImu_acc_z() const;
  double getImu_gyro_x() const;
  double getImu_gyro_y() const;
  double getImu_gyro_z() const;
  double getLidar_distance() const;
  double getSpeed() const;
  double getWind_speed() const;
  double getBattery_level() const;
  bool getObstacle_detected() const;

  friend std::ostream &operator<<(std::ostream &out, TelemetryData const &data);

  std::string to_string() const;
};

#endif // TELEMETRY_DATA_H
