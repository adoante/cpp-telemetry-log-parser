#include "ConfigParser.h"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

ConfigParser::ConfigParser() {};

std::string ConfigParser::removeSpace(std::string s) {
  for (int i = 0; i < s.size(); i++) {
    if (s[i] != ' ') {
      s = s.substr(i);
      break;
    }
  }

  for (int i = s.size(); i > s.size(); i--) {
    if (s[i] != ' ') {
      s = s.substr(0, i);
      break;
    }
  }

  return s;
}

std::unordered_map<std::string, ConfigType>
ConfigParser::parseConfig(std::filesystem::path file) {
  std::unordered_map<std::string, ConfigType> config;
  std::vector<ConfigType> temp;

  std::ifstream inputFile(file);
  std::string line;
  char del = '=';

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
  }

  return config;
}
