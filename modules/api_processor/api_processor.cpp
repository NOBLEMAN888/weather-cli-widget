#include "api_processor.h"

json ReadConfigFile(std::string path) {
  std::ifstream f(path);
  if (f.is_open()) {
    try {
      json data = json::parse(f);
      return data;
    }
    catch (const json::parse_error& err) {
      std::cerr << "Failed to parse config file! Check config validity!\n";
      exit(1);
    }
  } else {
    std::cerr << "Failed to open config file!\n";
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
                             cpr::Authentication{"user", "pass", cpr::AuthMode::BASIC}, cpr::Timeout{10000});
  if (r.status_code != 200) {
    std::cout << std::format("Waiting for response to the api-request for the city: {}\n", city);
  }
  while (r.status_code != 200) {
    r = cpr::Get(cpr::Url{
                     address}, cpr::Header{{"X-Api-Key", api_key}},
                 cpr::Authentication{"user", "pass", cpr::AuthMode::BASIC}, cpr::Timeout{10000});
  }
  json::parser_callback_t cb = [](int depth, json::parse_event_t event, json& parsed) {
    if (event == json::parse_event_t::key and parsed == json("Thumbnail")) {
      return false;
    } else {
      return true;
    }
  };
  try {
    json j_filtered = json::parse(r.text, cb);
    return j_filtered;
  }
  catch (const json::parse_error& err) {
    std::cerr << "Failed to parse api-response! Making another request...\n";
    return MakeCityRequest(city, api_key);
  }
}

json MakeWeatherRequest(WeatherRequestOptions options) {
  std::string address = GenerateWeatherRequestAddress(options);
  cpr::Response r = cpr::Get(cpr::Url{
                                 address},
                             cpr::Authentication{"user", "pass", cpr::AuthMode::BASIC}, cpr::Timeout{10000});
  if (r.status_code != 200) {
    std::cout << std::format("Waiting for response to the api-request for the city: {}\n", options.name);
  }
  while (r.status_code != 200) {
    r = cpr::Get(cpr::Url{
                     address},
                 cpr::Authentication{"user", "pass", cpr::AuthMode::BASIC}, cpr::Timeout{10000});
  }
  json::parser_callback_t cb = [](int depth, json::parse_event_t event, json& parsed) {
    if (event == json::parse_event_t::key and parsed == json("Thumbnail")) {
      return false;
    } else {
      return true;
    }
  };
  try {
    json j_filtered = json::parse(r.text, cb);
    return j_filtered;
  }
  catch (const json::parse_error& err) {
    std::cerr << "Failed to parse api-response! Making another request...\n";
    return MakeWeatherRequest(options);
  }
}
