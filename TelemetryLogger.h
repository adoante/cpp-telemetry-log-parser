#pragma once

#include <fstream>
#include <string>
#ifndef TELEMETRY_LOGGER_H

#define TELEMETRY_LOGGER_H

#include <filesystem>

enum LogLevel { INFO, WARNING, ERROR };

class TelemetryLogger {
private:
  std::ofstream ofs;
  std::string getLogLevelName(LogLevel level);

public:
  TelemetryLogger(std::filesystem::path file);
  ~TelemetryLogger();
  void log(LogLevel level, std::string msg, bool verbose);
};

#endif // ! TELEMETRY_LOGGER_H
