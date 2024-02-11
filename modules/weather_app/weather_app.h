#ifndef LAB7_MODULES_WEATHER_APP_WEATHER_APP_H_
#define LAB7_MODULES_WEATHER_APP_WEATHER_APP_H_

#include "../../modules/api_processor/api_processor.h"
#include "../../modules/event_listener/event_listener.h"
#include "../../modules/output_processor/output_processor.h"

#include "nlohmann/json.hpp"

#include <string>
#include <vector>
#include <cmath>

using json = nlohmann::json;

//struct WeatherInfo {
//  std::string day_time;
//  std::string weather_state;
//  size_t temperature;
//  size_t apparent_temperature;
//
//};
std::vector<WeatherRequestOptions> GetWeatherRequestOptions(json config);

void GetWeather(std::string path);

#endif //LAB7_MODULES_WEATHER_APP_WEATHER_APP_H_
