void changeSettings(String message){
  Serial.println("changing settings...");   
  
  int numberOfArguments = 0;
  for(int i = 0; i < message.length(); i++){
    if(message[i] == '=') numberOfArguments++;
  } 
  for(int i = 0; i < numberOfArguments; i++){
    String name = message.substring(0, message.indexOf('='));
    String value = message.substring(message.indexOf('=') + 1, message.indexOf('&'));
    message = message.substring(message.indexOf('&') + 1);
    Serial.println(name + ", " + value);

    if(name == "brightness"){
      setBright(value.toInt());
    } 
    if(name == "speed"){
      setSpeed(value.toInt());
    }
    if(name == "size"){
      setSize(value.toInt());
    }
    if(name == "R"){
      setRed(value.toInt());
    }
    if(name == "G"){
      setGreen(value.toInt());
    }
    if(name == "B"){
      setBlue(value.toInt());
    }
    if(name == "opacity"){
      setOpacity(value.toInt());
    }
  }
  Serial.println("complete");  
}

void changeMode(String message){
  Serial.println("changing mode...");  
  String name = message.substring(0, message.indexOf('='));
  String value = message.substring(message.indexOf('=') + 1, message.indexOf('&'));
  if(name == "mode"){
    setMode(value);
  }
}

void saveSettings(){
  Serial.println("start saving data to EEPROM"); 
  saveToMemory();
  Serial.println("fnished saving data to EEPROM"); 
}

void loadSettings(){
  Serial.println("start loading data from EEPROM"); 
  readFromMemory();
  Serial.println("fnished loading data from EEPROM");
}
