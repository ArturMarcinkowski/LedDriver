#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>

#define speedPin 100
#define ledPin D2
#define buttonPin LOW
#define NUMBER_OF_LEDS 300

const char* ssid     = "HUAWEI-B315-8855";         
const char* password = "8D1TQRHLFJ1";     

ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'
ESP8266WebServer server(80);    // Create a webserver object that listens for HTTP request on port 

Adafruit_NeoPixel myStrip = Adafruit_NeoPixel(NUMBER_OF_LEDS, ledPin);
float brightValue = 1;
float lightMode = 0;
float R = 0;
float G = 0;
float B = 0;
float rgbVariable= 0;
float rgbVariable2 = 0;
float stepValue = 1;

void setup() {
  myStrip.begin();
  wifiMulti.addAP(ssid, password); 

  server.on("/", HTTP_GET, handleRoot);     // Call the 'handleRoot' function when a client requests URI "/"
  server.on("/LED", HTTP_POST, handleLED);  // Call the 'handleLED' function when a POST request is made to URI "/LED"
  server.on("/LED", HTTP_GET, handleLED2); 
  server.onNotFound(handleNotFound);        // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"

  server.begin();   
}

void loop() {
  server.handleClient();                    // Listen for HTTP requests from clients
  
  if(lightMode == 0) stripLoopRainbow();
  if(lightMode == 1) stripLoopPulse();
  if(lightMode == 2) stripLoopWhite();
  myStrip.show();

  if(buttonPin == HIGH){
    lightMode++;
    if(lightMode == 3) lightMode = 0;
    delay(1000);
  }
}

void handleRoot() {                         // When URI / is requested, send a web page with a button to toggle the LED
  server.send(200, "text/html", "<form action=\"/LED\" method=\"POST\"><input type=\"submit\" value=\"Toggle LED\"></form>");
}

void handleLED() {                          // If a POST request is made to URI /LED
  server.sendHeader("Location","/");        // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}

void handleLED2() {                          // If a POST request is made to URI /LED
   if(server.hasArg("brightness")){
    brightValue = (float) server.arg("brightness").toInt() / 100;
    if(brightValue > 1) brightValue = 1;
    if(brightValue < 0) brightValue = 0;
  }
  server.send(200, "text/plain", "gg");  
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); 
}

void stripLoopRainbow(){
  rgbVariable2 += 10;
  if(rgbVariable2 >= 768) rgbVariable2 -= 768;
  rgbVariable = rgbVariable2;
  
  for(int i=0; i<NUMBER_OF_LEDS; i++){
    changeColors();
    rgbVariable += 7;
     if(rgbVariable >= 768) rgbVariable -= 768;
    myStrip.setPixelColor(i, R, G, B);
   } 
}

void stripLoopPulse(){
  changeColors();
  stepValue = speedPin;
  stepValue = pow(2, (stepValue / 90 - 6));
  if(stepValue > 256) stepValue = 256;
  if(stepValue < 0.032) stepValue = 0;
  
  rgbVariable += stepValue;
  if(rgbVariable >= 768) rgbVariable -= 768;
  
  for(int i=0; i<NUMBER_OF_LEDS; i++) {
    myStrip.setPixelColor(i, R, G, B);
  } 
}

void stripLoopWhite(){
  for(int i=0; i<NUMBER_OF_LEDS; i++){
    myStrip.setPixelColor(i, brightValue * 255, brightValue * 255, brightValue * 255);
  }
}

void changeColors(){
  R = 0;
  G = 0;
  B = 0;
  if(rgbVariable< 256){
    B = 255 - rgbVariable;
    R = rgbVariable;
  }
  else if(rgbVariable < 512){
    R = 511 - rgbVariable;
    G = rgbVariable - 256;
  }
  else{
    G = 767 - rgbVariable;
    B = rgbVariable - 512;
  }
  R = R * brightValue;
  G = G * brightValue;
  B = B * brightValue;
}
