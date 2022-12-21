#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

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
    http.begin("http://api.covid19api.com/country/philippines/status/confirmed?from=2020-10-30T00:00:00Z&to=2020-10-31T00:00:00Z");
    int httpCode = http.GET();
    //Check the returning code
    if (httpCode > 0) {
      // Parsing
      const size_t capacity = JSON_ARRAY_SIZE(2) + 2 * JSON_OBJECT_SIZE(10) + 310;
      DynamicJsonBuffer jsonBuffer(capacity);

      const char* json = "[{\"Country\":\"Philippines\",\"CountryCode\":\"PH\",\"Province\":\"\",\"City\":\"\",\"CityCode\":\"\",\"Lat\":\"12.88\",\"Lon\":\"121.77\",\"Cases\":378933,\"Status\":\"confirmed\",\"Date\":\"2020-10-30T00:00:00Z\"},{\"Country\":\"Philippines\",\"CountryCode\":\"PH\",\"Province\":\"\",\"City\":\"\",\"CityCode\":\"\",\"Lat\":\"12.88\",\"Lon\":\"121.77\",\"Cases\":380729,\"Status\":\"confirmed\",\"Date\":\"2020-10-31T00:00:00Z\"}]";

      JsonArray& root = jsonBuffer.parseArray(json);

      JsonObject& root_0 = root[0];
      const char* root_0_Country = root_0["Country"]; // "Philippines"
      const char* root_0_CountryCode = root_0["CountryCode"]; // "PH"
      const char* root_0_Province = root_0["Province"]; // ""
      const char* root_0_City = root_0["City"]; // ""
      const char* root_0_CityCode = root_0["CityCode"]; // ""
      const char* root_0_Lat = root_0["Lat"]; // "12.88"
      const char* root_0_Lon = root_0["Lon"]; // "121.77"
      long root_0_Cases = root_0["Cases"]; // 378933
      const char* root_0_Status = root_0["Status"]; // "confirmed"
      const char* root_0_Date = root_0["Date"]; // "2020-10-30T00:00:00Z"

      JsonObject& root_1 = root[1];
      const char* root_1_Country = root_1["Country"]; // "Philippines"
      const char* root_1_CountryCode = root_1["CountryCode"]; // "PH"
      const char* root_1_Province = root_1["Province"]; // ""
      const char* root_1_City = root_1["City"]; // ""
      const char* root_1_CityCode = root_1["CityCode"]; // ""
      const char* root_1_Lat = root_1["Lat"]; // "12.88"
      const char* root_1_Lon = root_1["Lon"]; // "121.77"
      long root_1_Cases = root_1["Cases"]; // 380729
      const char* root_1_Status = root_1["Status"]; // "confirmed"
      const char* root_1_Date = root_1["Date"]; // "2020-10-31T00:00:00Z"

      // Output to serial monitor
      // Displays Philippines Confirmed Cases from October 30, 2020 to October 31, 2020
      Serial.print("Country: ");
      Serial.println(root_0_Country);
      Serial.print("Country Code: ");
      Serial.println(root_0_CountryCode);
      Serial.print("Confirmed Cases on October 30, 2020: ");
      Serial.println(root_0_Cases);
      Serial.print("Confirmed Cases on October 31, 2020: ");
      Serial.println(root_1_Cases);

    }
    http.end();   //Close connection
  }
  // Delay
  delay(60000); //displays JSON API data every 60,000 milliseconds or 60 seconds (1 minute)
}
