#ifndef LAB7_MODULES_WEATHER_APP_WEATHER_APP_H_
#define LAB7_MODULES_WEATHER_APP_WEATHER_APP_H_

#include "../../modules/output_processor/output_processor.h"
#include "../../modules/api_processor/api_processor.h"
#include "../../modules/event_listener/event_listener.h"

#include "nlohmann/json.hpp"

#include <string>
#include <vector>
#include <cmath>
#include <ctime>

using json = nlohmann::json;

std::vector<WeatherRequestOptions> GetWeatherRequestOptions(json config);

void GetWeather(std::string path);

#endif //LAB7_MODULES_WEATHER_APP_WEATHER_APP_H_
