#include "TelemetryData.h"
#include "TelemetryParser.h"
#include "TelemetryValidator.h"
#include <iostream>
#include <vector>

int main() {

  std::filesystem::path path = "./uav_navigation_dataset.csv";

  TelemetryParser file(path);

  std::cout << file.getFilename() << "\n";

  std::vector<TelemetryData> data = file.readData();

  for (TelemetryData td : data) {
    std::cout << td << "\n";
  }

  TelemetryValidator val = TelemetryValidator(data[0]);

  std::cout << val.validate() << "\n";

  return 0;
}
