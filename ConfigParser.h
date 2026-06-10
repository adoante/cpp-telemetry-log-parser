#pragma once

#ifndef CONFIG_PARSER_H

#define CONFIG_PARSER_H

#include <filesystem>
#include <unordered_map>
#include <variant>

using ConfigType = std::variant<std::string, double>;

class ConfigParser {
private:
  ConfigParser();

  static std::string removeSpace(std::string s);

public:
  static std::unordered_map<std::string, ConfigType>
  parseConfig(std::filesystem::path file);
};

#endif // !CONFIG_PARSER_H
