#include "api_processor.h"

json ReadConfigFile(std::string path) {
  std::ifstream f(path);
  if (f.is_open()){
    json data = json::parse(f);
    return data;
  } else {
    std::cerr << "Failed to open config file!";
    exit(1);
  }
}
void ReplaceAll(std::string& str, const std::string& from, const std::string& to) {
  if (from.empty())
    return;
  size_t start_pos = 0;
  while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
    str.replace(start_pos, from.length(), to);
    start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
  }
}

std::string GenerateCityRequestAddress(std::string city) {
  ReplaceAll(city, " ", "_");
  std::string address = std::format("https://api.api-ninjas.com/v1/city?name={}", city);
  return address;
}

std::string GenerateWeatherRequestAddress(WeatherRequestOptions options) {
  std::string address = std::format(
      "https://api.open-meteo.com/v1/forecast?latitude={}&longitude={}&current=temperature_2m,relative_humidity_2m,apparent_temperature,rain,showers,snowfall,weather_code,wind_speed_10m,wind_direction_10m&hourly=temperature_2m,relative_humidity_2m,apparent_temperature,rain,showers,snowfall,weather_code,wind_speed_10m,wind_direction_10m&timezone=auto&forecast_days={}",
      options.latitude,
      options.longitude,
      options.forecast_period);
  return address;
}

json MakeCityRequest(std::string city, std::string api_key) {
  std::string address = GenerateCityRequestAddress(city);
  cpr::Response r = cpr::Get(cpr::Url{
                                 address}, cpr::Header{{"X-Api-Key", api_key}},
                             cpr::Authentication{"user", "pass", cpr::AuthMode::BASIC}, cpr::Timeout{1000});
  if (r.elapsed > 1) {
    std::cerr << std::format("The response waiting time has been exceeded for the city: {}", city);
  }
  if (r.status_code != 200){
    std::cout << std::format("Failed to make request for the city: {}", city);
  }
  json::parser_callback_t cb = [](int depth, json::parse_event_t event, json& parsed) {
    if (event == json::parse_event_t::key and parsed == json("Thumbnail")) {
      return false;
    } else {
      return true;
    }
  };
  json j_filtered = json::parse(r.text, cb);
  return j_filtered;
}

json MakeWeatherRequest(WeatherRequestOptions options) {
  std::string address = GenerateWeatherRequestAddress(options);
  cpr::Response r = cpr::Get(cpr::Url{
                                 address},
                             cpr::Authentication{"user", "pass", cpr::AuthMode::BASIC}, cpr::Timeout{1000});
  if (r.elapsed > 1) {
    std::cerr << std::format("The response waiting time has been exceeded for the city: {}", options.name);
  }
  if (r.status_code != 200){
    std::cout << std::format("Failed to make request for the city: {}", options.name);
  }
//  std::cout << "Status code: " << r.status_code << '\n';
  json::parser_callback_t cb = [](int depth, json::parse_event_t event, json& parsed) {
    if (event == json::parse_event_t::key and parsed == json("Thumbnail")) {
      return false;
    } else {
      return true;
    }
  };
  json j_filtered = json::parse(r.text, cb);
  return j_filtered;
}
