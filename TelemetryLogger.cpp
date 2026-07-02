#include "TelemetryLogger.h"
#include <fstream>
#include <iostream>
#include <string>

TelemetryLogger::TelemetryLogger(std::filesystem::path file) { ofs.open(file); }

TelemetryLogger::~TelemetryLogger() { ofs.close(); }

std::string TelemetryLogger::getLogLevelName(LogLevel level) {
  switch (level) {
  case LogLevel::INFO:
    return "INFO";
  case LogLevel::WARNING:
    return "WARNING";
  case LogLevel::ERROR:
    return "ERROR";
  default:
    return "DEFAULT";
  }
}

void TelemetryLogger::log(LogLevel level, std::string msg, bool verbose) {
  ofs << getLogLevelName(level) << ": " << msg << "\n";
  if (verbose) {
    std::cout << getLogLevelName(level) << ": " << msg << "\n";
  }
}
