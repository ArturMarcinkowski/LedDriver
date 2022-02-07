#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>

#define ledPin D2
#define NUMBER_OF_LEDS 24

ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'
ESP8266WebServer server(80);    // Create a webserver object that listens for HTTP request on port 
Adafruit_NeoPixel myStrip = Adafruit_NeoPixel(NUMBER_OF_LEDS, ledPin);

char* ssid     = "ssid";         
char* password = "password";  

float brightValue = 0.02;
float lightMode = 0;
float R = 0;
float G = 0;
float B = 0;
float colorBalance[3] = {1, 1, 1};
float rgbVariable= 0;
float rgbVariable2 = 0;
float stepValue = 1;
float rainbowSizeValue = 7;

void setup() {
  password = getWifiPassword();
  ssid = getWifiSSID();
//  wifiMulti.addAP(ssid, password); 
  setWifiConnection();
  myStrip.begin();

  server.on("/LED", HTTP_POST, handleLED); 
  server.on("/LED1", HTTP_POST, handleLED1); 
  server.on("/LED2", HTTP_POST, handleLED2); 
  server.on("/LED3", HTTP_POST, handleLED3); 
  server.on("/LED4", HTTP_GET, handleLED4); 
  server.onNotFound(handleNotFound);        // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"

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
