#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

#define stripPin D2
#define NUMBER_OF_LEDS 24
#define EEPROM_SIZE 16

ESP8266WebServer server(80);
Adafruit_NeoPixel myStrip = Adafruit_NeoPixel(NUMBER_OF_LEDS, stripPin);

char* ssid     = "ssid";         
char* password = "password";  

int lightMode = 0;
float brightValue = 0.04;
float stepValue = 10;
float rainbowSizeValue = 7;
float colorBalance[3] = {1, 1, 1};
float rgbVariable= 0;
float rgbVariable2 = 0;
float R = 0;
float G = 0;
float B = 0;

void setup() {
  password = getWifiPassword();
  ssid = getWifiSSID();
  setWifiConnection();  
  myStrip.begin();

  server.on("/change-settings", HTTP_POST, changeSettings);
  server.on("/save-settings", HTTP_GET, saveSettings); 
  server.on("/load-settings", HTTP_GET, loadSettings); 
  server.onNotFound(handleNotFound);        

  server.begin();   
}

void loop() {
  server.handleClient();                    // Listen for HTTP requests from clients
  if(lightMode == 0) stripLoopRainbow();
  if(lightMode == 1) stripLoopPulse();
  if(lightMode == 2) stripLoopWhite();
  myStrip.show();
  delay(5);
}
