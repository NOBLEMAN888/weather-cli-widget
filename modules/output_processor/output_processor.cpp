#include "output_processor.h"

std::string GetWeatherByCode(int code) {
  if (code == 0) {
    return "clear sky";
  }
  if (code == 1 || code == 2 || code == 3) {
    return "partly cloudy";
  }
  if (code == 45 || code == 48) {
    return "fog";
  }
  if (code == 51 || code == 53 || code == 55) {
    return "drizzle";
  }
  if (code == 56 || code == 57) {
    return "freezing drizzle";
  }
  if (code == 61 || code == 63) {
    return "rain";
  }
  if (code == 65) {
    return "heavy rain";
  }
  if (code == 66) {
    return "freezing rain";
  }
  if (code == 67) {
    return "heavy freezing rain";
  }
  if (code == 71 || code == 73) {
    return "snow fall";
  }
  if (code == 75) {
    return "heavy snow fall";
  }
  if (code == 77) {
    return "snow grains";
  }
  if (code == 80 || code == 81) {
    return "rain showers";
  }
  if (code == 82) {
    return "heavy rain showers";
  }
  if (code == 85) {
    return "snow showers";
  }
  if (code == 86) {
    return "heavy snow showers";
  }
  if (code == 95) {
    return "thunderstorm";
  }
  if (code == 96 || code == 99) {
    return "hail thunderstorm";
  }
  return std::to_string(code);
}
std::string GetWindDir(int degrees) {
  if (338 <= degrees || degrees <= 22) {
    return "North";
  }
  if (23 <= degrees && degrees <= 68) {
    return "North-East";
  }
  if (69 <= degrees && degrees <= 113) {
    return "East";
  }
  if (114 <= degrees && degrees <= 158) {
    return "South-East";
  }
  if (159 <= degrees && degrees <= 203) {
    return "South";
  }
  if (204 <= degrees && degrees <= 248) {
    return "South-West";
  }
  if (249 <= degrees && degrees <= 293) {
    return "West";
  }
  if (294 <= degrees && degrees <= 337) {
    return "North-West";
  }
  return std::to_string(degrees);
}
void PrintWeather(WeatherRequestOptions city, json request) {
  std::cout << "\x1B[2J\x1B[H";

  int kOvernightTime = 3;
  int kMorningTime = 9;
  int kAfternoonTime = 15;
  int kEveningTime = 21;

  int kDayTimeGapLeft = 17;
  int kDayTimeGapRight = 12;
  int kWeatherGap = 17;
  int kTemperatureGap = 13;
  int kHumidityGap = 14;
  int kWindSpeedGap = 9;
  int kWindDirGap = 10;
  int kRainGap = 17;
  int kShowersGap = 14;
  int kSnowfallGap = 13;

  std::cout << "--------" << city.name << "--------" << '\n';

  std::string current = std::string(request["current"]["time"]);
  ReplaceAll(current, "T", " ");
  std::cout << "/ Current | " << current << " \\" << '\n';

  std::cout << "Weather: " << std::setw(kWeatherGap) << GetWeatherByCode(int(request["current"]["weather_code"]))
            << '\n';
  std::cout << "Temperature: " << std::setw(kTemperatureGap)
            << std::format("{} ({}) \370C",
                           std::to_string(int(std::round(double(request["current"]["temperature_2m"])))),
                           std::to_string(
                               int(std::round(double(request["current"]["apparent_temperature"])))))
            << '\n';
  std::cout << "Humidity: " << std::setw(kHumidityGap)
            << to_string(request["current"]["relative_humidity_2m"]) << " %" << '\n';
  std::cout << "Wind speed: " << std::setw(kWindSpeedGap)
            << round(double(request["current"]["wind_speed_10m"])) << " km/h"
            << '\n';
  std::cout << "Wind direction: " << std::setw(kWindDirGap)
            << GetWindDir(int(request["current"]["wind_direction_10m"])) << '\n';
  std::cout << "Rain: " << std::setw(kRainGap)
            << double(request["current"]["rain"]) << " mm"
            << '\n';
  std::cout << "Showers: " << std::setw(kShowersGap)
            << double(request["current"]["showers"]) << " mm"
            << '\n';
  std::cout << "Snowfall: " << std::setw(kSnowfallGap)
            << double(request["current"]["snowfall"]) << " cm"
            << '\n';
  std::cout << '\n';

  for (size_t i = 0; i < city.forecast_period; ++i) {

    std::cout << std::setw(51) << "/ " << std::string(request["hourly"]["time"][i * 24]).substr(0, 10) << " \\" << '\n';

    std::cout << std::setw(kDayTimeGapLeft) << "Overnight" << std::setw(kDayTimeGapRight) << " | ";
    std::cout << std::setw(kDayTimeGapLeft) << "Morning" << std::setw(kDayTimeGapRight) << " | ";
    std::cout << std::setw(kDayTimeGapLeft) << "Afternoon" << std::setw(kDayTimeGapRight) << " | ";
    std::cout << std::setw(kDayTimeGapLeft) << "Evening";
    std::cout << '\n';

    std::cout << "Weather: " << std::setw(kWeatherGap) << GetWeatherByCode(int(request["hourly"]["weather_code"][i * 24
        + kOvernightTime]))
              << " | ";
    std::cout << "Weather: " << std::setw(kWeatherGap) << GetWeatherByCode(int(request["hourly"]["weather_code"][i * 24
        + kMorningTime]))
              << " | ";
    std::cout << "Weather: " << std::setw(kWeatherGap) << GetWeatherByCode(int(request["hourly"]["weather_code"][i * 24
        + kAfternoonTime]))
              << " | ";
    std::cout << "Weather: " << std::setw(kWeatherGap) << GetWeatherByCode(int(request["hourly"]["weather_code"][i * 24
        + kEveningTime]));
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

    std::cout << "Humidity: " << std::setw(kHumidityGap)
              << to_string(request["hourly"]["relative_humidity_2m"][i * 24
                  + kOvernightTime]) << " %" << " | ";
    std::cout << "Humidity: " << std::setw(kHumidityGap)
              << to_string(request["hourly"]["relative_humidity_2m"][i * 24
                  + kMorningTime]) << " %" << " | ";
    std::cout << "Humidity: " << std::setw(kHumidityGap)
              << to_string(request["hourly"]["relative_humidity_2m"][i * 24
                  + kAfternoonTime]) << " %" << " | ";
    std::cout << "Humidity: " << std::setw(kHumidityGap)
              << to_string(request["hourly"]["relative_humidity_2m"][i * 24
                  + kEveningTime]) << " %";
    std::cout << '\n';

    std::cout << "Wind speed: " << std::setw(kWindSpeedGap)
              << round(double(request["hourly"]["wind_speed_10m"][i * 24 + kOvernightTime])) << " km/h"
              << " | ";
    std::cout << "Wind speed: " << std::setw(kWindSpeedGap)
              << round(double(request["hourly"]["wind_speed_10m"][i * 24 + kMorningTime])) << " km/h"
              << " | ";
    std::cout << "Wind speed: " << std::setw(kWindSpeedGap)
              << round(double(request["hourly"]["wind_speed_10m"][i * 24 + kAfternoonTime])) << " km/h"
              << " | ";
    std::cout << "Wind speed: " << std::setw(kWindSpeedGap)
              << round(double(request["hourly"]["wind_speed_10m"][i * 24 + kEveningTime])) << " km/h";
    std::cout << '\n';

    std::cout << "Wind direction: " << std::setw(kWindDirGap)
              << GetWindDir(int(request["hourly"]["wind_direction_10m"][i * 24 + kOvernightTime])) << " | ";
    std::cout << "Wind direction: " << std::setw(kWindDirGap)
              << GetWindDir(int(request["hourly"]["wind_direction_10m"][i * 24 + kMorningTime])) << " | ";
    std::cout << "Wind direction: " << std::setw(kWindDirGap)
              << GetWindDir(int(request["hourly"]["wind_direction_10m"][i * 24 + kAfternoonTime])) << " | ";
    std::cout << "Wind direction: " << std::setw(kWindDirGap)
              << GetWindDir(int(request["hourly"]["wind_direction_10m"][i * 24 + kEveningTime]));
    std::cout << '\n';

    std::cout << "Rain: " << std::setw(kRainGap)
              << double(request["hourly"]["rain"][i * 24 + kOvernightTime]) << " mm"
              << " | ";
    std::cout << "Rain: " << std::setw(kRainGap)
              << double(request["hourly"]["rain"][i * 24 + kMorningTime]) << " mm"
              << " | ";
    std::cout << "Rain: " << std::setw(kRainGap)
              << double(request["hourly"]["rain"][i * 24 + kAfternoonTime]) << " mm"
              << " | ";
    std::cout << "Rain: " << std::setw(kRainGap)
              << double(request["hourly"]["rain"][i * 24 + kEveningTime]) << " mm";
    std::cout << '\n';

    std::cout << "Showers: " << std::setw(kShowersGap)
              << double(request["hourly"]["showers"][i * 24 + kOvernightTime]) << " mm"
              << " | ";
    std::cout << "Showers: " << std::setw(kShowersGap)
              << double(request["hourly"]["showers"][i * 24 + kMorningTime]) << " mm"
              << " | ";
    std::cout << "Showers: " << std::setw(kShowersGap)
              << double(request["hourly"]["showers"][i * 24 + kAfternoonTime]) << " mm"
              << " | ";
    std::cout << "Showers: " << std::setw(kShowersGap)
              << double(request["hourly"]["showers"][i * 24 + kEveningTime]) << " mm";
    std::cout << '\n';

    std::cout << "Snowfall: " << std::setw(kSnowfallGap)
              << double(request["hourly"]["snowfall"][i * 24 + kOvernightTime]) << " cm"
              << " | ";
    std::cout << "Snowfall: " << std::setw(kSnowfallGap)
              << double(request["hourly"]["snowfall"][i * 24 + kMorningTime]) << " cm"
              << " | ";
    std::cout << "Snowfall: " << std::setw(kSnowfallGap)
              << double(request["hourly"]["snowfall"][i * 24 + kAfternoonTime]) << " cm"
              << " | ";
    std::cout << "Snowfall: " << std::setw(kSnowfallGap)
              << double(request["hourly"]["snowfall"][i * 24 + kEveningTime]) << " cm";
    std::cout << '\n';
    std::cout << '\n';
  }
}
