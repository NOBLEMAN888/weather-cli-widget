#include "output_processor.h"

void PrintWeather(WeatherRequestOptions city, json request) {
  std::cout << "\x1B[2J\x1B[H";

  size_t kOvernightTime = 3;
  size_t kMorningTime = 9;
  size_t kAfternoonTime = 15;
  size_t kEveningTime = 21;

  size_t kDayTimeGapLeft = 17;
  size_t kDayTimeGapRight = 12;
  size_t kWeatherGap = 17;
  size_t kTemperatureGap = 13;
  size_t kWindGap = 9;
  size_t kRainGap = 20;
  size_t kShowersGap = 17;
  size_t kSnowfallGap = 16;


  std::cout << "--------" << city.name << "--------" << '\n';

  std::string current = std::string(request["current"]["time"]);
  ReplaceAll(current, "T", " ");
  std::cout << "/ Current | " << current << " \\" << '\n';

  std::cout << "Weather: " << std::setw(kWeatherGap)
            << to_string(request["current"]["weather_code"]) << '\n';
  std::cout << "Temperature: " << std::setw(kTemperatureGap)
            << std::format("{} ({}) \370C",
                           std::to_string(int(std::round(double(request["current"]["temperature_2m"])))),
                           std::to_string(
                               int(std::round(double(request["current"]["apparent_temperature"])))))
            << '\n';
  std::cout << "Wind speed: " << std::setw(kWindGap)
            << round(double(request["current"]["wind_speed_10m"])) << " km/h"
            << '\n';
  std::cout << "Rain: " << std::setw(kRainGap)
            << (request["current"]["rain"] == 0 ? "No" : "Yes")
            << '\n';
  std::cout << "Showers: " << std::setw(kShowersGap)
            << (request["current"]["showers"] == 0 ? "No" : "Yes")
            << '\n';
  std::cout << "Snowfall: " << std::setw(kSnowfallGap)
            << (request["current"]["snowfall"] == 0 ? "No" : "Yes")
            << '\n';
  std::cout << '\n';

  for (size_t i = 0; i < city.forecast_period; ++i) {

    std::cout << std::setw(51) << "/ " << std::string(request["hourly"]["time"][i * 24]).substr(0, 10) << " \\" << '\n';

    std::cout << std::setw(kDayTimeGapLeft) << "Overnight" << std::setw(kDayTimeGapRight) << " | ";
    std::cout << std::setw(kDayTimeGapLeft) << "Morning" << std::setw(kDayTimeGapRight) << " | ";
    std::cout << std::setw(kDayTimeGapLeft) << "Afternoon" << std::setw(kDayTimeGapRight) << " | ";
    std::cout << std::setw(kDayTimeGapLeft) << "Evening";
    std::cout << '\n';

    std::cout << "Weather: " << std::setw(kWeatherGap)
              << to_string(request["hourly"]["weather_code"][i * 24 + i * 24 + kOvernightTime]) << " | ";
    std::cout << "Weather: " << std::setw(kWeatherGap)
              << to_string(request["hourly"]["weather_code"][i * 24 + kMorningTime])
              << " | ";
    std::cout << "Weather: " << std::setw(kWeatherGap)
              << to_string(request["hourly"]["weather_code"][i * 24 + kAfternoonTime])
              << " | ";
    std::cout << "Weather: " << std::setw(kWeatherGap)
              << to_string(request["hourly"]["weather_code"][i * 24 + kEveningTime]);
    std::cout << '\n';

    std::cout << "Temperature: " << std::setw(kTemperatureGap)
              << std::format("{} ({}) \370C",
                             std::to_string(int(std::round(double(request["hourly"]["temperature_2m"][i * 24
                                 + kOvernightTime])))),
                             std::to_string(
                                 int(std::round(double(request["hourly"]["apparent_temperature"][i * 24
                                     + kOvernightTime])))))
              << " | ";
    std::cout << "Temperature: " << std::setw(kTemperatureGap)
              << std::format("{} ({}) \370C",
                             std::to_string(int(std::round(double(request["hourly"]["temperature_2m"][i * 24
                                 + kMorningTime])))),
                             std::to_string(
                                 int(std::round(double(request["hourly"]["apparent_temperature"][i * 24
                                     + kMorningTime])))))
              << " | ";
    std::cout << "Temperature: " << std::setw(kTemperatureGap)
              << std::format("{} ({}) \370C",
                             std::to_string(int(std::round(double(request["hourly"]["temperature_2m"][i * 24
                                 + kAfternoonTime])))),
                             std::to_string(
                                 int(std::round(double(request["hourly"]["apparent_temperature"][i * 24
                                     + kAfternoonTime])))))
              << " | ";
    std::cout << "Temperature: " << std::setw(kTemperatureGap)
              << std::format("{} ({}) \370C",
                             std::to_string(int(std::round(double(request["hourly"]["temperature_2m"][i * 24
                                 + kEveningTime])))),
                             std::to_string(
                                 int(std::round(double(request["hourly"]["apparent_temperature"][i * 24
                                     + kEveningTime])))));
    std::cout << '\n';

    std::cout << "Wind speed: " << std::setw(kWindGap)
              << round(double(request["hourly"]["wind_speed_10m"][i * 24 + kOvernightTime])) << " km/h"
              << " | ";
    std::cout << "Wind speed: " << std::setw(kWindGap)
              << round(double(request["hourly"]["wind_speed_10m"][i * 24 + kMorningTime])) << " km/h"
              << " | ";
    std::cout << "Wind speed: " << std::setw(kWindGap)
              << round(double(request["hourly"]["wind_speed_10m"][i * 24 + kAfternoonTime])) << " km/h"
              << " | ";
    std::cout << "Wind speed: " << std::setw(kWindGap)
              << round(double(request["hourly"]["wind_speed_10m"][i * 24 + kEveningTime])) << " km/h";
    std::cout << '\n';

    std::cout << "Rain: " << std::setw(kRainGap)
              << (request["hourly"]["rain"][i * 24 + kOvernightTime] == 0 ? "No" : "Yes")
              << " | ";
    std::cout << "Rain: " << std::setw(kRainGap)
              << (request["hourly"]["rain"][i * 24 + kMorningTime] == 0 ? "No" : "Yes")
              << " | ";
    std::cout << "Rain: " << std::setw(kRainGap)
              << (request["hourly"]["rain"][i * 24 + kAfternoonTime] == 0 ? "No" : "Yes")
              << " | ";
    std::cout << "Rain: " << std::setw(kRainGap)
              << (request["hourly"]["rain"][i * 24 + kEveningTime] == 0 ? "No" : "Yes");
    std::cout << '\n';

    std::cout << "Showers: " << std::setw(kShowersGap)
              << (request["hourly"]["showers"][i * 24 + kOvernightTime] == 0 ? "No" : "Yes")
              << " | ";
    std::cout << "Showers: " << std::setw(kShowersGap)
              << (request["hourly"]["showers"][i * 24 + kMorningTime] == 0 ? "No" : "Yes")
              << " | ";
    std::cout << "Showers: " << std::setw(kShowersGap)
              << (request["hourly"]["showers"][i * 24 + kAfternoonTime] == 0 ? "No" : "Yes")
              << " | ";
    std::cout << "Showers: " << std::setw(kShowersGap)
              << (request["hourly"]["showers"][i * 24 + kEveningTime] == 0 ? "No" : "Yes");
    std::cout << '\n';

    std::cout << "Snowfall: " << std::setw(kSnowfallGap)
              << (request["hourly"]["snowfall"][i * 24 + kOvernightTime] == 0 ? "No" : "Yes")
              << " | ";
    std::cout << "Snowfall: " << std::setw(kSnowfallGap)
              << (request["hourly"]["snowfall"][i * 24 + kMorningTime] == 0 ? "No" : "Yes")
              << " | ";
    std::cout << "Snowfall: " << std::setw(kSnowfallGap)
              << (request["hourly"]["snowfall"][i * 24 + kAfternoonTime] == 0 ? "No" : "Yes")
              << " | ";
    std::cout << "Snowfall: " << std::setw(kSnowfallGap)
              << (request["hourly"]["snowfall"][i * 24 + kEveningTime] == 0 ? "No" : "Yes");
    std::cout << '\n';
    std::cout << '\n';
  }
}
