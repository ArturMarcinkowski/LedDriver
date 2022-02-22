#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <EEPROM.h>

#define stripPin D2
#define NUMBER_OF_LEDS 300
#define EEPROM_SIZE 16

WiFiServer server(80);
Adafruit_NeoPixel myStrip = Adafruit_NeoPixel(NUMBER_OF_LEDS, stripPin);

char* ssid     = "ssid";         
char* password = "password";  

int lightMode = 0;
float brightValue = 0.04;
float stepValue = 10;
float rainbowSizeValue = 7;
float colorBalance[3] = {1, 1, 1}; //R, G, B
float rgbVariable= 0;
float rgbVariable2 = 0;
float R = 0;
float G = 0;
float B = 0;

void setup() {
  myStrip.begin();
  password = getWifiPassword();
  ssid = getWifiSSID();
  setWifiConnection();  
  server.begin();   
}

void loop() {
  if(lightMode == 0) stripLoopRainbow();
  if(lightMode == 1) stripLoopRainbow();
  if(lightMode == 2) stripLoopWhite();
  myStrip.show();

  WiFiClient client = server.available();
  if(client){
    if(client.available()){
      String message = client.readStringUntil('\r');
      Serial.println(message);
      client.flush();
      if(message.substring(0,4) == "POST"){
        handlePostRequests(message.substring(6, message.length() - 8));
      }
      if(message.substring(0,3) == "GET"){
        handleGetRequests(message.substring(5, message.length() - 8), client);
      }
    }
  }
  delay(10);
}
