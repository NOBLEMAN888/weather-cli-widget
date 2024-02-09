#include <iostream>
#include <fstream>
#include <string>
#include <cpr/cpr.h>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

int main(int argc, char** argv) {

  cpr::Response r = cpr::Get(cpr::Url{
                                 "https://api.open-meteo.com/v1/forecast?latitude=90&longitude=30&hourly=temperature_2m&forecast_days=16"},
                             cpr::Authentication{"user", "pass", cpr::AuthMode::BASIC}, cpr::Timeout{1000});
  if (r.elapsed > 1) {
    std::cout << "Too long to wait!";
    return 0;
  }
  std::cout << "Status code: " << r.status_code << '\n';
  std::ifstream f("../config.json");
  json data = json::parse(f);
  std::cout << data["City1"] << '\n';
//  cpr::Parameters{{"latitude", "90"}, {"longitude", "30"}, {"hourly", "temperature_2m"}, {"forecast_days", "16"}}
//  json j_complete = json::parse(r.text);
//  std::cout << std::setw(4) << j_complete << "\n\n";

  // define parser callback
  json::parser_callback_t cb = [](int depth, json::parse_event_t event, json& parsed) {
    // skip object elements with key "Thumbnail"
    if (event == json::parse_event_t::key and parsed == json("Thumbnail")) {
      return false;
    } else {
      return true;
    }
  };

  // parse (with callback) and serialize JSON
  json j_filtered = json::parse(r.text, cb);
//  std::cout << std::setw(4) << j_filtered << '\n';
std::cout << j_filtered["longitude"];
//  std::cout << r.header["Date"];
//  for (const std::pair<const std::basic_string<char>, std::basic_string<char>>& kv : r.header) {
//    std::cout << '\t' << kv.first << ':' << kv.second << '\n';
//  }
//  std::cout << "Text: " << r.GetCertInfos()[0][0] << '\n';


  return 0;
}
