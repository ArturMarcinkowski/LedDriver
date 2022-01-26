#include <Adafruit_NeoPixel.h>

#define brightnessPin A0
#define speedPin A5
#define ledPin 13
#define buttonPin 9
#define NUMBER_OF_LEDS 300

float brightValue = 0;
uint8_t lightMode = 0;
float R = 0;
float G = 0;
float B = 0;
float x = 0;
float stepValue = 1;

class Strip
{
public:
  uint8_t   effect;
  uint8_t   effects;
  uint16_t  effStep;
  unsigned long effStart;
  Adafruit_NeoPixel strip;
  Strip(uint16_t leds, uint8_t pin, uint8_t toteffects) : strip(NUMBER_OF_LEDS, ledPin, NEO_GRB + NEO_KHZ800) {
    effect = -1;
    effects = toteffects;
    Reset();
  }
  void Reset(){
    effStep = 0;
    effect = (effect + 1) % effects;
    effStart = millis();
  }
};

struct Loop
{
  uint8_t currentChild;
  uint8_t childs;
  bool timeBased;
  uint16_t cycles;
  uint16_t currentTime;
  Loop(uint8_t totchilds, bool timebased, uint16_t tottime) {currentTime=0;currentChild=0;childs=totchilds;timeBased=timebased;cycles=tottime;}
};

Strip my_strip(32, 3, 32 );
struct Loop strip0loop0(1, true, 3);

//[GLOBAL_VARIABLES]/////////////////////////////////////// mój kod:







void setup() {
  my_strip.strip.begin();
}

void loop() {
  brightValue = analogRead(brightnessPin);
  if(brightValue > 1000) brightValue = 1000;
  brightValue = pow(2, (brightValue /100)) / 1024;
  
  if(lightMode == 0) strips_loop();
  if(lightMode == 1) strips_loop_rainbow();
  if(lightMode == 2) strips_loop_white();

  if(digitalRead(buttonPin) == HIGH){
    lightMode++;
    if(lightMode == 3) lightMode = 0;
    delay(1000);
  }
}








void change_colors(){
  R = 0;
  G = 0;
  B = 0;
  if(x < 256){
    B = 255 - x;
    R = x;
  }
  else if(x < 512){
    R = 511 - x;
    G = x - 256;
  }
  else{
    G = 767 - x;
    B = x - 512;
  }
  R = R * brightValue;
  G = G * brightValue;
  B = B * brightValue;
}


void strips_loop_rainbow(){


  for(int i=0; i<NUMBER_OF_LEDS; i++) my_strip.strip.setPixelColor(i, R, G, B);
  change_colors();
  stepValue = analogRead(speedPin);
  if(stepValue > 1001) stepValue = 1001;
  stepValue = pow(2, ((stepValue) / 90 - 6));
  if(stepValue > 256) stepValue = 256;
  if(stepValue < 0.032) stepValue = 0;
  
  x+= stepValue;/////////////////////// tu jest stepValue
  if(x >= 768) x = x - 768;
  my_strip.strip.show();  
}

void strips_loop_white(){


  for(int i=0; i<NUMBER_OF_LEDS; i++) my_strip.strip.setPixelColor(i, brightValue * 255, brightValue * 255, brightValue * 255);

  my_strip.strip.show();  
}






//////////////////////////////////



void strips_loop() {
  if(strip0_loop0() & 0x01)
    my_strip.strip.show();
}

uint8_t strip0_loop0() {
  uint8_t ret = 0x00;
  switch(strip0loop0.currentChild) {
    case 0:
           ret = strip0_loop0_eff0();break;
  }
  if(ret & 0x02) {
    ret &= 0xfd;
    if(strip0loop0.currentChild + 1 >= strip0loop0.childs) {
      strip0loop0.currentChild = 0;
      if(++strip0loop0.currentTime >= strip0loop0.cycles) {strip0loop0.currentTime = 0; ret |= 0x02;}
    }
    else {
      strip0loop0.currentChild++;
    }
  };
  return ret;
}

uint8_t strip0_loop0_eff0() {
    // Strip ID: 0 - Effect: Rainbow - LEDS: 32
    // Steps: 32 - Delay: 20
    // Colors: 3 (255.0.0, 0.255.0, 0.0.255, )
    // Options: toLeft=true,
  float factor1, factor2;
  uint16_t ind;
  for(uint16_t j=0;j<NUMBER_OF_LEDS;j++) {
    ind = my_strip.effStep + j * 1/4;
    switch((int)((ind % 32) / 10.666666666666666)) {
      case 0: factor1 = (1.0 - ((float)(ind % 32 - 0 * 10.666666666666666) / 10.666666666666666)) * brightValue ;
              factor2 = ((float)((int)(ind - 0) % 32) / 10.666666666666666) * brightValue;
              my_strip.strip.setPixelColor(j, 255 * factor1 , 255 * factor2, 0);
              break;
      case 1: factor1 = (1.0 - ((float)(ind % 32 - 1 * 10.666666666666666) / 10.666666666666666)) * brightValue;
              factor2 = ((float)((int)(ind - 10.666666666666666) % 32) / 10.666666666666666) * brightValue;
              my_strip.strip.setPixelColor(j, 0, 255 * factor1 + 0 * factor2, 0 * factor1 + 255 * factor2);
              break;
      case 2: factor1 = (1.0 - ((float)(ind % 32 - 2 * 10.666666666666666) / 10.666666666666666)) * brightValue;
              factor2 = (float)((float)((int)(ind - 21.333333333333332) % 32) / 10.666666666666666) * brightValue; ////////
              my_strip.strip.setPixelColor(j, 255 * factor2, 0, 255 * factor1);
              break;
    }
  }
  if(my_strip.effStep >= 32) {my_strip.Reset(); return 0x03; }
  else my_strip.effStep++;
  return 0x01;
}