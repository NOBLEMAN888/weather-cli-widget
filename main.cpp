#include "modules/weather_app/weather_app.h"

int main() {
  std::string path = "../config.json";
  GetWeather(path);
  return 0;
}
