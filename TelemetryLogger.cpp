#include "TelemetryLogger.h"
#include <fstream>
#include <iostream>
#include <string>

TelemetryLogger::TelemetryLogger(std::filesystem::path file) { ofs.open(file); }

TelemetryLogger::~TelemetryLogger() { ofs.close(); }

void TelemetryLogger::log(LogLevel level, std::string msg, bool verbose) {
  ofs << level << ": " << msg << "\n";
  if (verbose) {
    std::cout << level << ": " << msg << "\n";
  }
}
