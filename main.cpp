#include "ConfigParser.h"

#include <filesystem>
#include <iostream>
#include <string>
#include <unordered_map>

int main() {

  std::filesystem::path configFile = "./anomaly.config";
  std::unordered_map<std::string, ConfigType> config =
      ConfigParser::parseConfig(configFile);

  for (auto i : config) {
    std::cout << i.first << ": ";

    std::visit([](const auto &value) { std::cout << value; }, i.second);

    std::cout << "\n";
  }

  return 0;
}
