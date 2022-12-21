/*
  #ESP8266 Web Server with AJAX
*/
//Declare libraries
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h>
//provide your own WiFi SSID and password
const char* ssid = "lubao";
const char* password = "thirteen";
//Create WebServer instance
ESP8266WebServer server(80);
String text = "";
double data;
void setup(void) {
  //Setup analog input pin
  pinMode(A0, INPUT);
  delay(1000);
  //For debugging
  Serial.begin(115200);
  //Initiate WiFi connection
  WiFi.begin(ssid, password); //begin WiFi connection
  Serial.println("");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  //Print your WiFi's SSID (might be insecure)
  Serial.println(ssid);
  Serial.print("IP address: ");
  //Print your local IP address (needed for browsing the app)
  Serial.println(WiFi.localIP());
  if (!SPIFFS.begin())
  {
    // Serious problem
    Serial.println("SPIFFS Mount failed");
  } else {
    Serial.println("SPIFFS Mount succesfull");
  }
  server.onNotFound([]() { // If the client requests any URI
    if (!handleFileRead(server.uri())) // send it if it exists
      server.send(404, "text/plain", "404: Not Found"); // otherwise, respond with a 404 (Not Found) error
  });
  //start web server
  server.begin();
  //Just stating things
  Serial.println("HTTP server started!");
}
void loop(void) {
  data = analogRead(A0);
  delay(1000);
  // Serial.println(data);
  server.handleClient();
}
bool handleFileRead(String path) { // send the right file to the client (if it exists)
  int bytesWritten;
  Serial.println("handleFileRead: " + path);
  if (path.endsWith("/")) path += "index.html"; // If a folder is requested, send the index file
  String contentType = getContentType(path); // Get the MIME type
  if (SPIFFS.exists(path)) { // If the file exists
    File file = SPIFFS.open(path, "r"); // Open it
    if (path == "/data.txt") {
      if (data > 512) {
        text = (String)data + " - Darkest"; // Convert sensor data to string
        server.send(200, "text/plain", text);
      }
      else if (data <= 512 && data > 256) {
        text = (String)data + " - Darker"; // Convert sensor data to string
        server.send(200, "text/plain", text);
      }
      else if (data <= 256) {
        text = (String)data + " - Dark"; // Convert sensor data to string
        server.send(200, "text/plain", text);
      }

    }
    size_t sent = server.streamFile(file, contentType);
    file.close(); // Then close the file again
    return true;
  }
  Serial.println("\tFile Not Found");
  return false; // If the file doesn't exist, return false
}
String getContentType(String filename) {
  if (filename.endsWith(".htm")) return "text/html";
  else if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".jpg")) return "image/jpeg";
  else if (filename.endsWith(".js")) return "text/js"; //to read .js files
  return "text/plain";
}
