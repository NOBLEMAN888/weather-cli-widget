#include "weather_app.h"

std::vector<WeatherRequestOptions> GetWeatherRequestOptions(json config) {
  ConfigStructure config_structure;
  CityRequestStructure city_request_structure;
  std::vector<WeatherRequestOptions> cities_info;
  json request;
  for (std::string city : config[config_structure.list_of_cities]) {
    if (!city.empty()) {
      request = MakeCityRequest(city);
      if (request.empty()) {
        std::cerr << std::format("Failed to get info about the city: {} \n", city);
      } else {
        cities_info.emplace_back(city,
                                 request[0][city_request_structure.latitude],
                                 request[0][city_request_structure.longitude],
                                 config[config_structure.forecast_period]);
      }
    }
  }
  return cities_info;
}
void GetWeather(std::string path) {
  json config = ReadConfigFile(path);
  std::vector<WeatherRequestOptions> cities_info = GetWeatherRequestOptions(config);
  json request;
  size_t current_city_index = 0;

  request = MakeWeatherRequest(cities_info[current_city_index]);
  PrintWeather(cities_info[current_city_index], request);
  std::cout << '\n';
  bool pressed = false;
  while(!ListenKeyPressed(VK_ESCAPE)) {
    if (ListenKeyPressed('N')){
      pressed = true;
//      if (current_city_index < cities_info.size() - 1) {
//        ++current_city_index;
//        request = MakeWeatherRequest(cities_info[current_city_index]);
//        PrintWeather(cities_info[current_city_index], request);
//        std::cout << '\n';
//      }
    } else if (ListenKeyPressed('P')) {
      if (current_city_index > 0) {
        --current_city_index;
        request = MakeWeatherRequest(cities_info[current_city_index]);
        PrintWeather(cities_info[current_city_index], request);
        std::cout << '\n';
      }
    } else if (ListenKeyPressed('+')) {
      std::cout << "More days!";
    } else if (ListenKeyPressed('-')) {
      std::cout << "Less days!";
    }
  }
  std::cout << "May your day be sunny! See you later...";
}
