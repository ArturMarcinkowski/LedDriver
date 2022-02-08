void setWifiConnection(){
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');
  WiFi.begin(ssid, password); 
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }
  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
}

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

void changeSettings(){
  Serial.println("changing settings...");                         
   if(server.hasArg("brightness")){
    setBright(server.arg("brightness").toInt());
  } 
  if(server.hasArg("speed")){
    setSpeed(server.arg("speed").toInt());
  }
  if(server.hasArg("size")){
    setSize(server.arg("size").toInt());
  }
  Serial.println("complete");  
}

void saveSettings(){
  Serial.println("start saving data to EEPROM"); 
  saveToMemory();
  Serial.println("fnished saving data to EEPROM"); 
  server.send(202, "text/plain", "done"); 
}

void loadSettings(){
  Serial.println("start loading data from EEPROM"); 
  readFromMemory();
  Serial.println("fnished loading data from EEPROM"); 
  server.send(202, "text/plain", "done"); 
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); 
}
