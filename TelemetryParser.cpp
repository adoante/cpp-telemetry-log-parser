#include "TelemetryParser.h"
#include "TelemetryData.h"
#include "TelemetryLogger.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

std::filesystem::path parserLogFile = "./ParserLog.txt";
TelemetryLogger parserLogger = TelemetryLogger(parserLogFile);

TelemetryParser::TelemetryParser() {}

TelemetryParser::TelemetryParser(std::filesystem::path file) {
  this->file = file;
}

std::vector<TelemetryData> TelemetryParser::readData() {
  std::vector<TelemetryData> data;

  std::ifstream inputFile(file);
  std::string line;
  char del = ',';
  bool headerSkip = false;

  while (getline(inputFile, line)) {
    std::vector<std::string> temp;
    std::stringstream ss(line);
    std::string t;

    while (getline(ss, t, del)) {
      temp.push_back(t);
    }

    if (headerSkip) {
      TelemetryData td = TelemetryData(
          temp[0], std::stod(temp[1]), std::stod(temp[2]), std::stod(temp[3]),
          std::stod(temp[4]), std::stod(temp[5]), std::stod(temp[6]),
          std::stod(temp[7]), std::stod(temp[8]), std::stod(temp[9]),
          std::stod(temp[10]), std::stod(temp[11]), std::stod(temp[12]),
          std::stod(temp[13]), temp[14] == "1");

      parserLogger.log(LogLevel::INFO,
                       "Parsed data point: [" + td.to_string() + "]\n", false);

      data.push_back(td);
    }

    temp.clear();
    headerSkip = true;
  }

  parserLogger.log(LogLevel::INFO,
                   "Parsed file '" + getFilename() + "' with " +
                       std::to_string(data.size()) + " data points.\n",
                   false);
  return data;
}

std::string TelemetryParser::getFilename() { return file.filename(); }
