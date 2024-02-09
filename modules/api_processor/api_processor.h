#ifndef LAB7_MODULES_API_PROCESSOR_API_PROCESSOR_H_
#define LAB7_MODULES_API_PROCESSOR_API_PROCESSOR_H_

#include <iostream>
#include <string>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

struct ConfigStructure {
  std::string city = "City";
  std::string period = "Period";
};
std::cout << ConfigStructure::city;
json ReadConfigFile(std::string& path);

std::string GenerateRequestAddress(json& options);

//void MakeRequest
#endif //LAB7_MODULES_API_PROCESSOR_API_PROCESSOR_H_
