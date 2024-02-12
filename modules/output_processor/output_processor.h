#ifndef LAB7_MODULES_OUTPUT_PROCESSOR_OUTPUT_PROCESSOR_H_
#define LAB7_MODULES_OUTPUT_PROCESSOR_OUTPUT_PROCESSOR_H_

#include "../../modules/api_processor/api_processor.h"

#include "nlohmann/json.hpp"

#include <format>
#include <string>
#include <iostream>

using json = nlohmann::json;

void PrintCertainHourWeather(json request, size_t index);

void PrintWeather(WeatherRequestOptions city, json request);

#endif //LAB7_MODULES_OUTPUT_PROCESSOR_OUTPUT_PROCESSOR_H_
