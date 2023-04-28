#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebSrv.h>

// Some variables we will need along the way
const char* ssid     = "Fablab";
const char* password = "Fabricationlab1"; 
const char* PARAM_MESSAGE = "message"; 
int webServerPort = 80;
int led = D10;

// Setting up our webserver
AsyncWebServer server(webServerPort);

// This function will be called when human will try to access undefined endpoint
void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setup() {
  pinMode(led, OUTPUT);

  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");

  // We want to know the IP address so we can send commands from our computer to the device
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Greet human when it tries to access the root / endpoint.
  // This is a good place to send some documentation about other calls available if you wish.
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "Hello, world");
  });

  // Usage IP_ADDRESS/led?state=1 where /led is our endpoint and ?state=on is a variable definition.
  // You can also chain variables like this: /led?sate=off&color=blue
  server.on("/led", HTTP_GET, [](AsyncWebServerRequest *request){
    bool state; // LED state 
    if (request->hasParam("state")) {
      // The incoming params are Strings
      String param = request->getParam("state")->value();
      // .. so we have to interpret or cast them
      state = ((param == "on") ? HIGH : LOW); // Look up Terary Operator (e.g. https://www.programiz.com/cpp-programming/ternary-operator)
    } else {
      state = LOW;
    }

    // Send back message to human
    String response = "Turning LED ";
    response += state ? "on" : "off"; 
    request->send(200, "text/plain", response);

    // Operate LED
    digitalWrite(led, state);
  });

  // If human tries endpoint no exist, exec this function
  server.onNotFound(notFound);

  Serial.print("Starting web server on port ");
  Serial.println(webServerPort);
  server.begin();
} 

void loop() {
  // Nothing needed here at the moment
}