#ifndef LAB7_MODULES_API_PROCESSOR_API_PROCESSOR_H_
#define LAB7_MODULES_API_PROCESSOR_API_PROCESSOR_H_

#include "cpr/cpr.h"
#include "nlohmann/json.hpp"

#include <string>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

struct ConfigStructure {
  std::string api_key = "api_key";
  std::string list_of_cities = "list_of_cities";
  std::string forecast_period = "forecast_period";
  std::string updating_frequency = "updating_frequency";
};
struct CityRequestStructure {
  std::string name = "name";
  std::string latitude = "latitude";
  std::string longitude = "longitude";
};
struct WeatherRequestStructure {
  std::string list_of_cities = "list_of_cities";
  std::string forecast_period = "forecast_period";
  std::string updating_frequency = "updating_frequency";
};
struct WeatherRequestOptions {
  std::string name;
  double latitude;
  double longitude;
  size_t forecast_period;
//  ? size_t last_time_updated;
  WeatherRequestOptions(std::string name, double latitude, double longitude, size_t forecast_period) :
      name{name}, latitude{latitude}, longitude{longitude}, forecast_period{forecast_period} {};
};

json ReadConfigFile(std::string path);

void ReplaceAll(std::string& str, const std::string& from, const std::string& to);

std::string GenerateCityRequestAddress(std::string city);

std::string GenerateWeatherRequestAddress(WeatherRequestOptions options);

json MakeCityRequest(std::string city, std::string api_key);

json MakeWeatherRequest(WeatherRequestOptions options);
#endif //LAB7_MODULES_API_PROCESSOR_API_PROCESSOR_H_
