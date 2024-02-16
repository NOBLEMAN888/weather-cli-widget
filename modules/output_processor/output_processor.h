#ifndef LAB7_MODULES_OUTPUT_PROCESSOR_OUTPUT_PROCESSOR_H_
#define LAB7_MODULES_OUTPUT_PROCESSOR_OUTPUT_PROCESSOR_H_

#include "../../modules/api_processor/api_processor.h"

#include "nlohmann/json.hpp"

#include <format>
#include <string>
#include <iostream>

using json = nlohmann::json;

std::string GetWeatherByCode(int code);

std::string GetWindDir(int degrees);

void PrintWeather(WeatherRequestOptions city, json request);

#endif //LAB7_MODULES_OUTPUT_PROCESSOR_OUTPUT_PROCESSOR_H_
