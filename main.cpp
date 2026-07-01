#include "ConfigParser.h"
#include "TelemetryAnomaly.h"
#include "TelemetryData.h"
#include "TelemetryLogger.h"
#include "TelemetryParser.h"
#include "TelemetryValidator.h"

#include <filesystem>
#include <string>
#include <unordered_map>

int main() {
  // Logger
  std::filesystem::path logFile = "./MainLog.txt";
  TelemetryLogger logger = TelemetryLogger(logFile);

  // Parse UAV Data
  std::filesystem::path path = "./uav_navigation_dataset.csv";
  TelemetryParser file(path);

  std::string msg = "Parsing '" + file.getFilename() + "'";
  logger.log(LogLevel::INFO, msg, true);

  std::vector<TelemetryData> data = file.readData();

  // Read Validator Config file
  std::filesystem::path valConfigFile = "./validator.config";

  std::unordered_map<std::string, ConfigType> valConfig =
      ConfigParser::parseConfig(valConfigFile);

  msg = "Configuring Validator using config file: '" + valConfigFile.string() +
        "'";
  logger.log(LogLevel::INFO, msg, true);

  // Validate UAV data
  bool valResult = true;

  for (const auto &validate : data) {

    TelemetryValidator val = TelemetryValidator(validate, valConfig);
    valResult = valResult &= val.validate();
  }

  if (valResult) {
    logger.log(LogLevel::INFO, "Validation Successful. Valid UAV data.", true);
  } else {
    logger.log(LogLevel::ERROR, "Validation Failed. Invalid UAV data.", true);
  }

  // Read Anomaly Config file
  std::filesystem::path anomConfigFile = "./anomaly.config";

  std::unordered_map<std::string, ConfigType> anomConfig =
      ConfigParser::parseConfig(anomConfigFile);

  msg = "Configuring Anomaly Detector using config file: '" +
        anomConfigFile.string() + "'";
  logger.log(LogLevel::INFO, msg, true);

  // Detect anomalies in UAV data
  bool result = true;

  for (const auto &anomaly : data) {
    TelemetryAnomaly anom(anomaly, anomConfig);

    result = result &= anom.anomaly();
  }

  if (result) {
    logger.log(LogLevel::INFO, "No anomalies detected.", true);
  } else {
    logger.log(LogLevel::INFO, "Anomalies detected.", true);
  }

  return 0;
}
