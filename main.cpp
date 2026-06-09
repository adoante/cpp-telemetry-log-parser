#include "TelemetryAnomaly.h"
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

  TelemetryValidator val = TelemetryValidator(data[0]);

  std::cout << val.validate() << "\n";

  TelemetryAnomaly anom = TelemetryAnomaly(data[1]);

  std::cout << anom.anomaly() << "\n";

  return 0;
}
