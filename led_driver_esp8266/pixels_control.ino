void stripLoopRainbow(){
  rgbVariable2 += stepValue;
  if(rgbVariable2 >= 768) rgbVariable2 -= 768;
  rgbVariable = rgbVariable2;
  
  for(int i=0; i<NUMBER_OF_LEDS; i++){
    changeColors();
    rgbVariable += rainbowSizeValue;
     if(rgbVariable >= 768) rgbVariable -= 768;
    myStrip.setPixelColor(i, R, G, B);
   } 
}

void stripLoopPulse(){
  changeColors();
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

  R += 20;
  G += 20;
  B += 20;
  R = R * colorBalance[0];
  G = G * colorBalance[1];
  B = B * colorBalance[2];
//  int maximum = max(R, max(G, B));
//  if(maximum != 0 && lightMode == 1){
//    R = 255 * R / maximum;
//    G = 255 * G / maximum;
//    B = 255 * B / maximum;
//  }



//  int newR = R * colorBalance[0] + colorBalance[0] / (colorBalance[0] + colorBalance[1]) * colorBalance[2] * B + colorBalance[0] / (colorBalance[0] + colorBalance[2]) * colorBalance[1] * G;
//  int newG = G * colorBalance[1] + colorBalance[1] / (colorBalance[1] + colorBalance[0]) * colorBalance[2] * B + colorBalance[1] / (colorBalance[1] + colorBalance[2]) * colorBalance[0] * R;
//  int newB = B * colorBalance[2] + colorBalance[2] / (colorBalance[2] + colorBalance[0]) * colorBalance[1] * G + colorBalance[2] / (colorBalance[2] + colorBalance[1]) * colorBalance[0] * R;
//  R = newR;
//  G = newG;
//  B = newB;
  int maximum = max(R, max(G, B));
  if(maximum != 0){
    R = 255 * R / maximum;
    G = 255 * G / maximum;
    B = 255 * B / maximum;
  }



  
  R = R * brightValue;
  G = G * brightValue;
  B = B * brightValue;
}
