void setBright(int bright){
  brightValue = (float) bright / 10;
  brightValue = pow(2, brightValue) / 1024;
  if(brightValue > 1) brightValue = 1;
  if(brightValue < 0) brightValue = 0;
  Serial.println("changing brightness to: " + String(brightValue));  
}

void setSpeed(int speed){
  stepValue = (float) speed;
  stepValue = pow(2, (stepValue / 9 - 6));
  if(stepValue > 256) stepValue = 256;
  if(stepValue < 0.032) stepValue = 0;
  Serial.println("changing speed to: " + String(stepValue));  
}

void setSize(int size){  
  rainbowSizeValue = (float) size;
  if(rainbowSizeValue > 50) rainbowSizeValue = 50;
  if(rainbowSizeValue < 1) rainbowSizeValue = 1;
  Serial.println("changing size to: " + String(rainbowSizeValue));  
}

void setMode(String mode){
  if(mode == "nextMode"){
      lightMode++;
      if(lightMode == 3) lightMode = 0;
    }else{
      lightMode = mode.toInt();
      if(lightMode > 2) lightMode = 2; 
      if(lightMode < 0) lightMode = 0; 
    }
}
