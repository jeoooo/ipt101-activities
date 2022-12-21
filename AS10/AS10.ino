#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h>

// WiFi Parameters
const char* ssid = "lubao";
const char* password = "thirteen";


void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
  Serial.println("");
  Serial.print("Connected to ");
  //Print your WiFi's SSID (might be insecure)
  Serial.println(ssid);
  Serial.print("IP address: ");
  //Print your local IP address (needed for browsing the app)
  Serial.println(WiFi.localIP());
}

void loop() {
  // Check WiFi Status
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;  //Object of class HTTPClient
    http.begin("http://api.openweathermap.org/data/2.5/weather?q=Tokyo&appid=d7fac22aacea383eda7afd1d1e7f09ad&units=metric");
    int httpCode = http.GET();
    //Check the returning code
    if (httpCode > 0) {
      // Parsing
      const size_t capacity = JSON_ARRAY_SIZE(1) + 2 * JSON_OBJECT_SIZE(1) + 2 * JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(14) + 440;
      DynamicJsonBuffer jsonBuffer(capacity);

      const char* json = "{\"coord\":{\"lon\":139.69,\"lat\":35.69},\"weather\":[{\"id\":520,\"main\":\"Rain\",\"description\":\"light intensity shower rain\",\"icon\":\"09n\"}],\"base\":\"stations\",\"main\":{\"temp\":16.83,\"feels_like\":15.14,\"temp_min\":16,\"temp_max\":17.78,\"pressure\":1014,\"humidity\":82},\"visibility\":8000,\"wind\":{\"speed\":4.1,\"deg\":10},\"rain\":{\"1h\":0.29},\"clouds\":{\"all\":75},\"dt\":1604316361,\"sys\":{\"type\":1,\"id\":8074,\"country\":\"JP\",\"sunrise\":1604264647,\"sunset\":1604303124},\"timezone\":32400,\"id\":1850144,\"name\":\"Tokyo\",\"cod\":200}";

      JsonObject& root = jsonBuffer.parseObject(json);

      float coord_lon = root["coord"]["lon"]; // 139.69
      float coord_lat = root["coord"]["lat"]; // 35.69

      JsonObject& weather_0 = root["weather"][0];
      int weather_0_id = weather_0["id"]; // 520
      const char* weather_0_main = weather_0["main"]; // "Rain"
      const char* weather_0_description = weather_0["description"]; // "light intensity shower rain"
      const char* weather_0_icon = weather_0["icon"]; // "09n"

      const char* base = root["base"]; // "stations"

      JsonObject& main = root["main"];
      float main_temp = main["temp"]; // 16.83
      float main_feels_like = main["feels_like"]; // 15.14
      int main_temp_min = main["temp_min"]; // 16
      float main_temp_max = main["temp_max"]; // 17.78
      int main_pressure = main["pressure"]; // 1014
      int main_humidity = main["humidity"]; // 82

      int visibility = root["visibility"]; // 8000

      float wind_speed = root["wind"]["speed"]; // 4.1
      int wind_deg = root["wind"]["deg"]; // 10

      float rain_1h = root["rain"]["1h"]; // 0.29

      int clouds_all = root["clouds"]["all"]; // 75

      long dt = root["dt"]; // 1604316361

      JsonObject& sys = root["sys"];
      int sys_type = sys["type"]; // 1
      int sys_id = sys["id"]; // 8074
      const char* sys_country = sys["country"]; // "JP"
      long sys_sunrise = sys["sunrise"]; // 1604264647
      long sys_sunset = sys["sunset"]; // 1604303124

      long timezone = root["timezone"]; // 32400
      long id = root["id"]; // 1850144
      const char* name = root["name"]; // "Tokyo"
      int cod = root["cod"]; // 200
      // Output to serial monitor
      //      Display the following data from the API on the Arduino Serial Monitor. Make sure to show only parsed JSON data:
      //      -- temperature
      //      -- feels_like
      //      -- humidity
      //      -- pressure
      //      -- wind
      //      -- clouds
      //      -- visibility
      //      -- precipitation
    
      Serial.println("\nTime Parsed: Monday, November 2, 2020 7:46:10 PM");
      Serial.print("City: ");
      Serial.println(name);

      Serial.print("Forecast: ");
      Serial.println(weather_0_description);

      Serial.print("Temperature: ");
      Serial.print(main_temp);
      Serial.println("°C");

      Serial.print("Feels Like: ");
      Serial.print(main_feels_like);
      Serial.println("°C");

      Serial.print("Humidity: ");
      Serial.print(main_humidity );
      Serial.println("%");

      Serial.print("Atmospheric pressure (sea level): ");
      Serial.print(main_pressure);
      Serial.println(" hPa");

      Serial.print("Wind Speed: ");
      Serial.print(wind_speed);
      Serial.println(" meters/sec");

      Serial.print("Cloudiness: ");
      Serial.print(clouds_all);
      Serial.println("%");

      Serial.print("Visibility: ");
      Serial.print(visibility);
      Serial.println("m");

      //      Since there is no precipitation value (available only in XML format)
      //      I'll just show the rain volume in mm
      Serial.print("Precipitation (Rain volume for the last 1 hour): ");
      Serial.print(rain_1h);
      Serial.println("mm");

    }
    http.end();   //Close connection
  }
  // Delay
  delay(60000); //displays JSON API data every 60,000 milliseconds or 60 seconds (1 minute)
}
