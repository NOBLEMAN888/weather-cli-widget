#include "output_processor.h"

void PrintCertainHourWeather(json request, size_t index){
  std::string current = std::string(request["hourly"]["time"][index]);
  ReplaceAll(current, "T", " ");
  std::cout << current << '\n';
  std::cout << "Weather: " << request["hourly"]["weather_code"][index] << '\n';
  std::cout << "Temperature: " << request["hourly"]["temperature_2m"][index] << " ("
            << request["hourly"]["apparent_temperature"][index] << ") \370C" << '\n';
  std::cout << "Wind speed: " << request["hourly"]["wind_speed_10m"][index] << " km/h" << '\n';

  std::cout << "Rain: " << (request["hourly"]["rain"][index] == 0 ? "No" : "Yes") << '\n';
  std::cout << "Showers: " << (request["hourly"]["showers"][index] == 0 ? "No" : "Yes") << '\n';
  std::cout << "Snowfall: " << (request["hourly"]["snowfall"][index] == 0 ? "No" : "Yes") << '\n';
}
void PrintWeather(WeatherRequestOptions city, json request) {
  system("cls");

  std::cout << "--------" << city.name << "--------"  << '\n';
  std::cout << '\n';

  std::string current = std::string(request["current"]["time"]);
  ReplaceAll(current, "T", " ");
  std::cout << "Current | " << current << '\n';

  std::cout << "Weather: " << request["current"]["weather_code"] << '\n';
  std::cout << "Temperature: " << request["current"]["temperature_2m"] << " ("
            << request["current"]["apparent_temperature"] << ") \370C" << '\n';
  std::cout << "Wind speed: " << request["current"]["wind_speed_10m"] << " km/h" << '\n';

  std::cout << "Rain: " << (request["current"]["rain"] == 0 ? "No" : "Yes") << '\n';
  std::cout << "Showers: " << (request["current"]["showers"] == 0 ? "No" : "Yes") << '\n';
  std::cout << "Snowfall: " << (request["current"]["snowfall"] == 0 ? "No" : "Yes") << '\n';

  for (size_t i = 0; i < city.forecast_period; ++i) {
    std::cout << '\n';
    std::cout << "Morning | ";
    PrintCertainHourWeather(request, 9);
    std::cout << '\n';
    std::cout << "Afternoon | ";
    PrintCertainHourWeather(request, 15);
    std::cout << '\n';
    std::cout << "Evening | ";
    PrintCertainHourWeather(request, 21);
    std::cout << '\n';
    std::cout << "Overnight | ";
    PrintCertainHourWeather(request, 3);
    std::cout << '\n';
  }
  std::cout << '\n';

//  for (int i = 3; i < 22; i += 6){
//    std::cout << round(int(request["hourly"]["temperature_2m"][i])) << ' ';
//  }
//  std::string a = "dfgfgfd";
//  std::cout << std::format("\x1b[31m{}", a);
}
