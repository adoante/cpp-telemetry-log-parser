#include "ConfigParser.h"
#include "TelemetryLogger.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::filesystem::path file = "./ConfigParserLogs.txt";
TelemetryLogger configParserLogger = TelemetryLogger(file);

ConfigParser::ConfigParser() {};

std::string ConfigParser::removeSpace(std::string s) {
  configParserLogger.log(LogLevel::INFO,
                         "Removing white space from: '" + s + "'", false);

  for (int i = 0; i < s.size(); i++) {
    if (s[i] != ' ') {
      s = s.substr(i);
      break;
    }
  }

  for (int i = s.size() - 1; i >= 0; i--) {
    if (s[i] != ' ') {
      s = s.substr(0, i + 1);
      break;
    }
  }

  configParserLogger.log(LogLevel::INFO,
                         "Removed white space from: '" + s + "'", false);

  return s;
}

std::unordered_map<std::string, ConfigType>
ConfigParser::parseConfig(std::filesystem::path file) {
  std::unordered_map<std::string, ConfigType> config;
  std::vector<ConfigType> temp;

  std::ifstream inputFile(file);
  std::string line;
  char del = '=';

  std::string msg = "Using '" + file.string() + "' to set configuration.";
  configParserLogger.log(LogLevel::INFO, msg, false);

  while (getline(inputFile, line)) {
    std::stringstream ss(line);

    if (ss.str().empty()) {
      continue;
    }

    std::string key;
    std::string value;

    getline(ss, key, del);
    getline(ss, value);

    key = removeSpace(key);
    value = removeSpace(value);

    if (value[0] == '"' and value[value.size() - 1] == '"') {
      value = value.substr(1, value.size() - 2);
      config.insert({key, value});
    } else {
      config.insert({key, std::stod(value)});
    }

    msg = "Setting " + key + " to " + value;
    configParserLogger.log(LogLevel::INFO, msg, false);
  }

  return config;
}
