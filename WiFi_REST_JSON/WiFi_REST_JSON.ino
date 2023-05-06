// This is untested ChatGPT code, 
// but gives an example how to use the ArduinoJson library

#include <ArduinoJson.h>
#include <WiFi.h> // For ESP32
//#include <ESP8266WiFi.h> // Uncomment this line for ESP8266
#include <ESPAsyncWebServer.h>

// Replace with your network credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// Create an instance of AsyncWebServer
AsyncWebServer server(80);

void setup() {
  // Start the serial communication
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Serve the JSON payload
  server.on("/json", HTTP_GET, [](AsyncWebServerRequest *request) {
    // Sample JSON payload
    const char* json = "{\"sensor\":\"temperature\",\"value\":25}";

    // Allocate a JSON buffer and parse the payload
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, json);

    // Access the data in the JSON object
    const char* sensor = doc["sensor"];
    int value = doc["value"];

    // Print the data to the serial monitor
    Serial.print("Sensor: ");
    Serial.println(sensor);
    Serial.print("Value: ");
    Serial.println(value);

    // Send the JSON payload as the HTTP response
    request->send(200, "application/json", json);
  });

  // Start the server
  server.begin();
}

void loop() {
  // Nothing to do here
}
