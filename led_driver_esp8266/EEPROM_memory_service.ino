void saveToMemory(){
  EEPROM.begin(EEPROM_SIZE);
  delay(20);
  int address = 0;
  
  EEPROM.put(address, lightMode);
  address += sizeof(lightMode);

  EEPROM.put(address, brightValue);
  address += sizeof(brightValue);

  EEPROM.put(address, stepValue);
  address += sizeof(stepValue);

  EEPROM.put(address, rainbowSizeValue);
  address += sizeof(rainbowSizeValue);
 
  EEPROM.end();
}

void readFromMemory(){
  EEPROM.begin(EEPROM_SIZE);
  delay(20);
  int address = 0;
  
  EEPROM.get(address, lightMode);
  address += sizeof(lightMode);

  EEPROM.get(address, brightValue);
  address += sizeof(brightValue);

  EEPROM.get(address, stepValue);
  address += sizeof(stepValue);

  EEPROM.get(address, rainbowSizeValue);
  address += sizeof(rainbowSizeValue);
  
  EEPROM.end();
}
