#ifndef LAB7_MODULES_OUTPUT_PROCESSOR_OUTPUT_PROCESSOR_H_
#define LAB7_MODULES_OUTPUT_PROCESSOR_OUTPUT_PROCESSOR_H_

#include "nlohmann/json.hpp"

using json = nlohmann::json;


void PrintWeather(json request);

#endif //LAB7_MODULES_OUTPUT_PROCESSOR_OUTPUT_PROCESSOR_H_
