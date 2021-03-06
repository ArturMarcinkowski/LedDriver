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

void handlePostRequests(String message){
  message.replace(" ", "");
  String request = message.substring(0, message.indexOf('?'));
  Serial.println(request);
  
  if(request == "change-settings"){
    changeSettings(message.substring(request.length() + 1));
  }
  if(request == "change-mode"){
    changeMode(message.substring(request.length() + 1));
  }
  if(request == "change-rgb-balance"){
    changeSettings(message.substring(request.length() + 1));
    balanceColors();
  }
}

void handleGetRequests(String message, WiFiClient client){
  String request = message.substring(0, message.indexOf('?'));
  request.replace(" ", "");
  Serial.println(request);

  if(request == "load-settings"){
    loadSettings();
  }
  if(request == "save-settings"){
    saveSettings();
  }
}
