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
  R = 255 * brightValue * (colorBalance[0] * opacity + 1 - opacity ); 
  G = 255 * brightValue * (colorBalance[1] * opacity + 1 - opacity ); 
  B = 255 * brightValue * (colorBalance[2] * opacity + 1 - opacity ); 
  
  for(int i=0; i<NUMBER_OF_LEDS; i++){
    myStrip.setPixelColor(i, R, G, B);
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

  R = R * (1 - opacity) + 255 * colorBalance[0] * opacity;
  G = G * (1 - opacity) + 255 * colorBalance[1] * opacity;
  B = B * (1 - opacity) + 255 * colorBalance[2] * opacity; 

//  int maximum = max(R, max(G, B));
//  if(maximum != 0){
//    R = 255 * R / maximum;
//    G = 255 * G / maximum;
//    B = 255 * B / maximum;
//  }
  R = R * brightValue;
  G = G * brightValue;
  B = B * brightValue;
  if(R > 255) R = 255;
  if(G > 255) G = 255;
  if(B > 255) B = 255;
}
