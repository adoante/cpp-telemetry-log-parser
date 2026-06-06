#pragma once

#ifndef TELEMETRY_PARSER_H
#define TELEMETRY_PARSER_H

#include "TelemetryData.h"
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

class TelemetryParser {
private:
  std::filesystem::path file;

public:
  TelemetryParser();
  TelemetryParser(std::filesystem::path file);

  std::vector<TelemetryData> readData();

  void setFile(std::filesystem::path file);

  std::string getFilename();
};

#endif // !TELEMETRY_PARSER_H
