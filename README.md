# HapGrab
## 1. Description
![Demo Gif](https://videoapi-muybridge.vimeocdn.com/animated-thumbnails/image/e7b8a2b5-0df9-4f0c-88be-426a93814a0d.gif?ClientID=vimeo-core-prod&Date=1671954016&Signature=fe06f929ae3c2d25bf72e7fc472b54ce7dbd1c75)
![Demo Gif 2](https://videoapi-muybridge.vimeocdn.com/animated-thumbnails/image/22a3e30b-2522-436b-9fc9-66449bc0d7e8.gif?ClientID=vimeo-core-prod&Date=1671954204&Signature=3846d5d5ca744750d53c82f5a46b2181102cd9aa)
- Interface for Grab-and-move 3D interacetion and haptic feedback
- [Video Demo](https://vimeo.com/784200640)
## 2. Features
- Bluetooth Serial (Send and receive data) [[1]](#1)
- Get and calculate flex sensor angle value [[2]](#2)
- LCD display control [[3]](#3)
- 6DoF Acc/Gryo Sensor
- Haptic feedback [[4]](#4)
- 3D Generative art on openFrameworks
## 3. Specimen
### 3-1. Hardware
Check out fritzing file for more information.
- ESP32 Dev Module (runs on 3.3V)
- ILI9341 TFT LCD Display
- Flex Sensor
- Qwiic 6DoF LSM6DSO
- Lilypad Vide Board
- ~~Qwiic Haptic Driver DA7280~~
### 3-2. Power Module
- 18650 Li-ion Battery
- Li-ion power module
- DC/DC Stepup module
- Toggle switch
### 3-3. Software Requirements
- TFT_eSPI library (by bodmer) modified for ILI9341 and ESP32 (this project) [Go to repo](https://github.com/chanulee/TFT_eSPI)
- Qwiic 6DoF LSM6DSO Library [Hookup Guide](https://learn.sparkfun.com/tutorials/qwiic-6dof-lsm6dso-breakout-hookup-guide)
- ofxSimpleSerial by LeoColomb [Go to repo](https://github.com/LeoColomb/ofxSimpleSerial)
## 4. References
1. Bluetooth Serial for ESP32 <a name="1" href="https://randomnerdtutorials.com/esp32-bluetooth-classic-arduino-ide/" target="_blank">Tutorial</a>
2. Flex sensor <a name="2" href="https://learn.sparkfun.com/tutorials/flex-sensor-hookup-guide?_ga=2.13438583.1502922294.1671452785-154993728.1671452785" target="_blank">Hookup Guide</a> 
3. TFT LCD Display <a name="3" href="https://www.youtube.com/watch?v=rq5yPJbX_uk" target="_blank">Tutorial Video</a>  
4. <a name="4">Haptic Feedback using LilyPad Vibe Board</a>
5. https://junkiyoshi.com/2019/10/page/5/
## 5. Memo / Trial & Error
- Set to ESP32 Dev Module in IDE.
- Button on right side of the microusb port should be pressed when uploading code. Press the other button to reboot after uploading.
- You should set COM port as "send" on the device when you connect to ESP32 (Windows).
- Quit openFrameworks app (ofApp) that gets serial data before uploading data to ESP32.
- Haptic feedback of LilyPad Vibe Board feels a little bit weak on wrist. But still stronger than Qwiic Haptic Driver DA7280.
- [Qwiic 6DoF Gyro/Acc LSM6DSO library](https://learn.sparkfun.com/tutorials/qwiic-6dof-lsm6dso-breakout-hookup-guide) and [Qwiic Haptic Driver DA7280 library](https://learn.sparkfun.com/tutorials/qwiic-haptic-driver-da7280-hookup-guide?_ga=2.22013947.1502922294.1671452785-154993728.1671452785) crashes on arduino ide    
---
Physical Computing, Fall 2022     
Advisor Prof. Sangwook Lee  
Dept. of Art & Technology, Sogang University
  
Hapgrab is built upon wearable interface [alpha](https://github.com/chanulee/alpha), which was funded by [National Research Foundation Korea](https://www.nrf.re.kr/eng/index) as University Innovation program, 2022
