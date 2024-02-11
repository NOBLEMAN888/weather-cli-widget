#include "weather_app.h"

std::vector<WeatherRequestOptions> GetWeatherRequestOptions(json config){
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
  for (WeatherRequestOptions city : cities_info){
    request = MakeWeatherRequest(city);
    std::cout << city.name << ' ';
    std::cout << round(int(request["current"]["temperature_2m"])) << ' ';
    for (int i = 3; i < 22; i += 6){
      std::cout << round(int(request["hourly"]["temperature_2m"][i])) << ' ';
    }
    std::cout << '\n';
  }
}
