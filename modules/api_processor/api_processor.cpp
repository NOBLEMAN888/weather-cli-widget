#include "api_processor.h"

json MakeRequest(std::string& address) {
//  "https://api.open-meteo.com/v1/forecast?latitude=90&longitude=30&hourly=temperature_2m&forecast_days=16"
  cpr::Response r = cpr::Get(cpr::Url{
                                 address},
                             cpr::Authentication{"user", "pass", cpr::AuthMode::BASIC}, cpr::Timeout{1000});
  if (r.elapsed > 1) {
    std::cout << "Too long to wait!";
  }
  std::cout << "Status code: " << r.status_code << '\n';
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

json ReadConfigFile(std::string& path) {
  std::ifstream f(path);
  json data = json::parse(f);
  return data;
}

std::string GenerateRequestAddress(json& options) {
  return std::string();
}
