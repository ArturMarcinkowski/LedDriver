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

void setRed(int red){
  colorBalance[0] = (float) red / 100;
  Serial.println("changing red balance to: " + String(colorBalance[0]));  
}
void setGreen(int green){
  colorBalance[1] = (float) green / 100;
  Serial.println("changing green balance to: " + String(colorBalance[1])); 
}
void setBlue(int blue){
  colorBalance[2] = (float) blue / 100;
  Serial.println("changing blue balance to: " + String(colorBalance[2])); 
}

void balanceColors(){
  float maximum = max(colorBalance[0], max(colorBalance[1], colorBalance[2]));
  if(maximum != 1){
    Serial.println("balancing colors by division by: " + String(maximum));
    Serial.println("");
    for(int i = 0; i < 3; i++){
      colorBalance[i] = (float) colorBalance[i] / maximum;
      Serial.print(String(colorBalance[i]) + ", ");
    }
  }
}

void setMode(String mode){
  Serial.println("from: " + String(lightMode));  
  if(mode == "next"){
    lightMode++;
    if(lightMode == 3) lightMode = 0;
  }else{
    lightMode = mode.toInt();
    if(lightMode > 2) lightMode = 2; 
    if(lightMode < 0) lightMode = 0; 
  }
  Serial.println("to: " + String(lightMode) + " (" + mode + ")");  
}
