#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid = "lubao";
const char* password = "thirteen";

ESP8266WebServer server(80);   //instantiate server at port 80 (http port)

String page = "";
int LEDPin = 13;
void setup(void) {
  //the HTML of the web page
  page = "<h1>Name: Jeo Carlo M. Lubao </h1>"
         "<h1>Address: Roseville Subd., Lanang, Davao City</h1>"
         "<h2>Contact Number: 0916 665 8126 </h2>"
         "<br>"
         "<h1>Education</h1>"
         "<br>"
         "<h2>Elementary</h2>"
         "<h3 style=""color:blue"">Holy Cross of Davao College</h3>"
         "<h2>Junior High School<h2>" 
         "<h3 style=""color:red"">Holy Cross of Davao College</h3>"
         "<h2>Senior High School</h2>"
         "<h3 style=""color:#FFA500"">Holy Cross of Davao College | Strand: Science, Technology, Engineering, Mathematics (STEM)</h3>"
         "<h2>Tertiary Education (College)</h2>"
         "<h3 style=""color:#808080"">Holy Cross of Davao College | Course: Bachelor of Science in Information Technology (BSIT)</h3>"
         "<br>"
         "<h1>Accomplishments</h1>"
         "<ul>"
         "<li><h3>Holy Cross of Davao College (STEM - Grade 11) SY. 2017-2018 - With Honors </h3></li>"
         "<li><h3>Mindanao-Wide IT Olympiad 2020 (February 11, 2020) Programming Competition - Champion</h3></li>"
         "<li><h3>Holy Cross of Davao College (STEM - Grade 11) SY. 2017-2018 - With Honors </h3></li>"
         "<li><h3>Techno Fair 2020 (March 3 - 6,2020) Programming Competition | BSIT Category - 2nd Runner-Up</h3></li>"
         "</ul>";
  //make the LED pin output and initially turned off
  pinMode(LEDPin, OUTPUT);
  digitalWrite(LEDPin, LOW);

  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password); //begin WiFi connection
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", []() {
    server.send(200, "text/html", page);
  });
  server.on("/LEDOn", []() {
    server.send(200, "text/html", page);
    digitalWrite(LEDPin, HIGH);
    delay(1000);
  });
  server.on("/LEDOff", []() {
    server.send(200, "text/html", page);
    digitalWrite(LEDPin, LOW);
    delay(1000);
  });
  server.begin();
  Serial.println("Web server started!");
}

void loop(void) {
  server.handleClient();
}