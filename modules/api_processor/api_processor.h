#ifndef LAB7_MODULES_API_PROCESSOR_API_PROCESSOR_H_
#define LAB7_MODULES_API_PROCESSOR_API_PROCESSOR_H_

#include <iostream>
#include <string>
#include "nlohmann/json.hpp"
#include <fstream>
#include <cpr/cpr.h>
using json = nlohmann::json;

struct ConfigStructure {
  std::string city = "City";
  std::string period = "Period";
};

json ReadConfigFile(std::string& path);

std::string GenerateRequestAddress(json& options);

json MakeRequest(std::string& address);

#endif //LAB7_MODULES_API_PROCESSOR_API_PROCESSOR_H_
