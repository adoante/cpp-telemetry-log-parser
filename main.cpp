#include "ConfigParser.h"
#include "TelemetryAnomaly.h"
#include "TelemetryData.h"
#include "TelemetryParser.h"
#include "TelemetryValidator.h"

#include <filesystem>
#include <iostream>
#include <string>
#include <unordered_map>

int main() {

  // Parse UAV Data
  std::filesystem::path path = "./uav_navigation_dataset.csv";
  TelemetryParser file(path);

  std::cout << file.getFilename() << "\n";

  std::vector<TelemetryData> data = file.readData();

  // Read Validator Config file
  std::filesystem::path valConfigFile = "./validator.config";

  std::unordered_map<std::string, ConfigType> valConfig =
      ConfigParser::parseConfig(valConfigFile);

  /*
  for (auto i : valConfig) {
    std::cout << i.first << ": ";

    std::visit([](const auto &value) { std::cout << value; }, i.second);

    std::cout << "\n";
  }
  */

  // Validate UAV data
  TelemetryValidator val = TelemetryValidator(data[0], valConfig);

  std::cout << (val.validate() ? "Valid UAV Data" : "Invalid UAV Data") << "\n";

  // Read Anomaly Config file
  std::filesystem::path anomConfigFile = "./anomaly.config";

  std::unordered_map<std::string, ConfigType> anomConfig =
      ConfigParser::parseConfig(anomConfigFile);

  /*
    for (auto i : anomConfig) {
      std::cout << i.first << ": ";

      std::visit([](const auto &value) { std::cout << value; }, i.second);

      std::cout << "\n";
    }
  */

  // Detect anomalies in UAV data
  TelemetryAnomaly anom = TelemetryAnomaly(data[1], anomConfig);

  std::cout << (anom.anomaly() ? "No anomalies detected" : "Anomaly Detected")
            << "\n";

  return 0;
}
