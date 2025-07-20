# ECUMaster Black + ESP32 3.5inch

[![ESP32](https://img.shields.io/badge/board-ESP32-blue.svg)](https://www.espressif.com/en/products/socs/esp32)
[![ECUMaster](https://img.shields.io/badge/device-ECUMaster-black.svg)](https://www.ecumaster.com)
[![Bluetooth](https://img.shields.io/badge/communication-Bluetooth-brightgreen.svg)](https://en.wikipedia.org/wiki/Bluetooth)
[![LVGL](https://img.shields.io/badge/UI-LVGL-purple.svg)](https://lvgl.io/)
[![Arduino](https://img.shields.io/badge/framework-Arduino-blue.svg)](https://www.arduino.cc)
[![License: GPL v3](https://img.shields.io/badge/license-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0.en.html)
[![Language: C++](https://img.shields.io/badge/language-C++-orange.svg)](https://isocpp.org)

## Description

Based on project [ECUMaster-Black-ESP32-Bluetooth-Display](https://github.com/danuecumaster/ECUMaster-Black-ESP32-Bluetooth-Display) more dedicated for 2.8inch.
This project supports 3.5 inch from aliexpress to display some information from your **ECUMaster Black ECU** :

- Automatic Bluetooth reconnection
- Real-time monitoring of engine vitals
- Custom alerts (CEL, coolant temp, RPM, Lambda, MAP, etc.) via display
- TFT screen GUI with **LVGL**

## Tested On

- ESP32_3248S035C (or ESP32 JC2432W328  but need extra config, currently there is a mirroring effect...)
- Arduino Core
- ECUMaster Black with EDL-1
- LVGL v9.3

## Installation

1. Clone this repo
2. Open the project in VS-Code
3. Install recommended extensions like platform.io
4. set ECUMaster bluethooth device's Mac Address in `emu_mac_address.h`
5. Now you can build/upload and monitor via the platform.io VSCode plugin. All dependencies are installed automatically
6. Upload to ESP32
7. Optional - Connect an active 3.0-3.3V buzzer to GPIO Pin 22 (for warnings/CEL)
8. Pair with ECUMaster Black BT adapter
9. Enjoy real-time data on-screen!

## LED Behavior

- FLashing blue: Looking for connection
- Light blue: trying to connect to your emu
- Blue: connected
- Red:  error occured
  - if not connected, failed to connect to your emu
  - if connected, check engine light ON
- White: 88% max rpm
- Flashing White: 95% max rpm


## How to adapt the display

The values are displayed by components stored in `src\components`. 
Let's take lambda value as an example:
- create the c file in this dir
  - it contains 3 functions:
    - drawing function  `void draw_lambda(lv_obj_t* ui_screen)`
    - setting function `void set_lambda(EMUSerial emuSerial)`
    - destroying function (not used atm)
- add the declaration file (.h) in `include\components` 
- Include this .h in `includes\components.h`
- the location of the component is defined by `offsetX` and `offsetY` in the drawing function
- The drawing function is added in the `void ui_Screen1_screen_init(void)` from `src\ui_Screen1.cpp`
- the setting function is added in the `void ui_Screen1_render(EMUSerial emuSerial)` from `src\ui_Screen1.cpp`

IF you want to adapt the rendering, plz refer to the lvgl documents: https://docs.lvgl.io/9.3/

Here the values handled by this project:
```c
struct emu_data_t {
  uint16_t RPM;                  // RPM
  uint16_t MAP;                  // kPa
  uint8_t TPS;                   // %
  int8_t IAT;                    // C
  float Batt;                    // V
  int8_t IgnAngle;               // deg
  float pulseWidth;              // ms
  uint16_t EGT1;                 // C
  uint16_t EGT2;                 // C
  float knockLevel;              // V
  float dwellTime;               // ms
  float wboAFR;                  // AFR
  int8_t gear;                   //
  uint8_t Baro;                  // kPa
  float analogIn1;               // V
  float analogIn2;               // V
  float analogIn3;               // V
  float analogIn4;               // V
  float analogIn5;               // V
  float analogIn6;               // V
  float injDC;                   // %
  int8_t emuTemp;                // C
  float oilPressure;             // Bar
  uint8_t oilTemperature;        // C
  float fuelPressure;            // Bar
  int16_t CLT;                   // C
  float flexFuelEthanolContent;  // %
  int8_t ffTemp;                 // C
  float wboLambda;               // λ
  uint16_t vssSpeed;             // km/h
  uint16_t deltaFPR;             // KPa
  int8_t fuelLevel;              // %
  uint8_t tablesSet;             // tabel
  float lambdaTarget;            // λ
  float secondaryPulseWidth;     // ms
  uint16_t cel;
  uint16_t knockCount;
};
```


## Dependencies

- [BluetoothSerial](https://github.com/espressif/arduino-esp32/tree/master/libraries/BluetoothSerial)
- [LVGL](https://lvgl.io)
- [eSPI](https://github.com/Bodmer/TFT_eSPI)

## Hardware Used

- **ESP32_3248S035C**  
  [🛒 AliExpress link](https://www.aliexpress.com/w/wholesale-ESP32_3248S035C.html)
  
  [Documentation](https://drive.google.com/drive/folders/1Sk4sIXgLAqPZ03BzYb0IwUftMXJ9QMLN?usp=sharing)

- **ECU**  
[ECUMaster Black](https://www.ecumaster.com/products/emu-black/)

  [EMU CAN Bluetooth Adapter](https://ecumasterusa.com/products/bluetooth-adapter-for-ecumaster-emu-can-bus)

## Demo Videos
- initialization

[![Watch on YouTube](https://img.youtube.com/vi/OAoq9HcoHR0/0.jpg)](https://youtu.be/OAoq9HcoHR0)

- Alerting (here lambda value)

[![Watch on YouTube](https://img.youtube.com/vi/loQKHL9-78k/0.jpg)](https://youtu.be/loQKHL9-78k)

- Gear display + knocks detection (knocks is the sum of total knocks since the last ignition)

[![Watch on YouTube](https://img.youtube.com/vi/wxS327UacaE/0.jpg)](https://youtu.be/wxS327UacaE)

- On track

[![Watch on YouTube](https://img.youtube.com/vi/xY6AGlObUdg/0.jpg)](https://youtu.be/xY6AGlObUdg)

## License

This project is licensed under **GPL v3**.  
See the [LICENSE](https://www.gnu.org/licenses/gpl-3.0.en.html) file for more info.
