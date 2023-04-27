#include <WiFi.h>

const char* ssid     = "Fablab";
const char* password = "Fabricationlab1";   

WiFiServer server(80); // Webservers usually listen on port 80

int connectionCounter = 1;
int btn = D6;
int led = D10;

void setup()
{
  pinMode(btn, INPUT_PULLUP);
  pinMode(led, OUTPUT);

  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin(); // Start webserver
} 

void loop()
{
  // Do we have someone connecting?
  WiFiClient client = server.available();

  if (client) {
    Serial.println();
    Serial.println("Client connected.");

    if (client.connected()) {

      String incoming = "";
      while (client.available()) {
        char c = client.read();
        incoming += c;
      }

      //incoming = incoming.trim();
      //Serial.println(incoming);

      // Extract just the first line
      
      int charCounter = 0;
      String firstLine = "";
      while (incoming.charAt(charCounter) != '\n') {
        firstLine += incoming.charAt(charCounter);
        charCounter++;
      }

      Serial.println(firstLine);

      // Extract query
      charCounter = 0;
      bool firstSpace = false;
      String query = "";
      while (charCounter < firstLine.length()) {
        char c = firstLine.charAt(charCounter);
        
        if (c == ' ') {
          if (firstSpace) {
            break;
          } else {
            firstSpace = true;
          }
        }
        
        if (firstSpace == true && c != ' ') {
          query += c;
        }

        charCounter++;
      }

      Serial.println(query);

      String response = "";

      if (query == "/turnLedOn") {
        response = "Turning LED on.";
        digitalWrite(led, HIGH);
      } else if (query == "/turnLedOff") {
        response = "Turning LED off";
        digitalWrite(led, LOW);
      } else if (query == "/getButtonState") {
        response = "Button state is ";
        int buttonState = digitalRead(btn);
        response += String(buttonState);
      } else {
        response = "Unknown request: ";
        response += query;
      }

      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("Connection: close");
      client.println();
      client.println(response);

      /*
      client.println("<html>");

      int btnState = digitalRead(btn);
      client.print("Button down? ");
      client.print(btnState);
      client.println("<br>");
      client.print("This was attempt number ");
      client.print(connectionCounter);
      client.println("<br>");
      connectionCounter++;

      client.println("</html>");
      */

      // give the web browser time to receive the data
      delay(1);

      client.stop();
      Serial.println("Client disconnected");
    }
  }
}