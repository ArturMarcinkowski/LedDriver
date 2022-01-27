#include <Adafruit_NeoPixel.h>

#define brightnessPin A0
#define speedPin A5
#define ledPin 13
#define buttonPin 9
#define NUMBER_OF_LEDS 300

Adafruit_NeoPixel myStrip = Adafruit_NeoPixel(NUMBER_OF_LEDS, ledPin);
float brightValue = 0;
float lightMode = 0;
float R = 0;
float G = 0;
float B = 0;
float rgbVariable= 0;
float rgbVariable2 = 0;
float stepValue = 1;

void setup() {
  myStrip.begin();
}

void loop() {
  brightValue = analogRead(brightnessPin);
  if(brightValue > 1000) brightValue = 1000;
  brightValue = pow(2, (brightValue /100)) / 1024;
  
  if(lightMode == 0) stripLoopRainbow();
  if(lightMode == 1) stripLoopPulse();
  if(lightMode == 2) stripLoopWhite();
  myStrip.show();

  if(digitalRead(buttonPin) == HIGH){
    lightMode++;
    if(lightMode == 3) lightMode = 0;
    delay(1000);
  }
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
  stepValue = analogRead(speedPin);
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
