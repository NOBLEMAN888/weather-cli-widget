#include "weather_app.h"

std::vector<WeatherRequestOptions> GetWeatherRequestOptions(json config) {
  ConfigStructure config_structure;
  CityRequestStructure city_request_structure;
  std::vector<WeatherRequestOptions> cities_info;
  json request;
  for (std::string city : config[config_structure.list_of_cities]) {
    if (!city.empty()) {
      request = MakeCityRequest(city, config[config_structure.api_key]);
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
  ConfigStructure config_structure;
  std::vector<WeatherRequestOptions> cities_info = GetWeatherRequestOptions(config);
  json request;
  size_t current_city_index = 0;

  request = MakeWeatherRequest(cities_info[current_city_index]);
  PrintWeather(cities_info[current_city_index], request);
  time_t update_timer = time(nullptr);
  time_t button_timer = clock();
  while(!ListenKeyPressed(VK_ESCAPE)) {
    if (time(nullptr) - update_timer >= config[config_structure.updating_frequency]){
      request = MakeWeatherRequest(cities_info[current_city_index]);
      PrintWeather(cities_info[current_city_index], request);
      update_timer = time(nullptr);
    }
    if (ListenKeyPressed('N') && clock() - button_timer >= 200){
      button_timer = clock();
      if (current_city_index < cities_info.size() - 1) {
        ++current_city_index;
        request = MakeWeatherRequest(cities_info[current_city_index]);
        PrintWeather(cities_info[current_city_index], request);
        update_timer = time(nullptr);
      }
    } else if (ListenKeyPressed('P') && clock() - button_timer >= 200) {
      button_timer = clock();
      if (current_city_index > 0) {
        --current_city_index;
        request = MakeWeatherRequest(cities_info[current_city_index]);
        PrintWeather(cities_info[current_city_index], request);
        update_timer = time(nullptr);
      }
    } else if (ListenKeyPressed(VK_OEM_PLUS) && clock() - button_timer >= 200) {
      button_timer = clock();
      ++cities_info[current_city_index].forecast_period;
      request = MakeWeatherRequest(cities_info[current_city_index]);
      PrintWeather(cities_info[current_city_index], request);
      update_timer = time(nullptr);
    } else if (ListenKeyPressed(VK_OEM_MINUS) && clock() - button_timer >= 200) {
      button_timer = clock();
      if (cities_info[current_city_index].forecast_period > 1) {
        --cities_info[current_city_index].forecast_period;
        request = MakeWeatherRequest(cities_info[current_city_index]);
        PrintWeather(cities_info[current_city_index], request);
        update_timer = time(nullptr);
      }
    }
  }
  std::cout << "May your day be sunny! See you later...";
}
