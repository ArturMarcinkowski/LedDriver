# LedDriver
My old project with Arduino to control WS1228B led strips

For this project I was using Arduino Uno R3, two 10KΩ potentiometers, button, 10KΩ resistor and of course WS1228B led strip

![Arduino Uno](https://user-images.githubusercontent.com/61290919/155426272-dd133d40-84a0-4e75-883c-5d55e64eb47f.png)

I use potentiometers to control brightness and color change speed of the LEDs.  
Button is used to change light mode. There are 3 modes:
1) rainbow (default on startup) - strip in all RGB colors
2) pulse - whole strip in one color changing in time
3) white - white light for casual lightning places  

I put all components in 3D printed box (3D models are included in project files)

![models](https://user-images.githubusercontent.com/61290919/155428059-c94f6602-3fe5-40bf-98f9-d7520fcedaab.png)

# ESP8266

In future development of this project I decided to focus on moving it to another board - nodeMCU v3 + ESP8266.  
With this board I will control LEDs by WiFi instead of potentiometers which give me opportunity to add more features.  

Current status:
- [x] basic WiFi handling
- [ ] more light modes
- [x] saving settings to EEPROM memory
- [ ] design new box
- [x] more basic settings
- [ ] better HTML config page
- [ ] config page load from ESP instead of other files







