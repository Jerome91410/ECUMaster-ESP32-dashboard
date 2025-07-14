# 🚗 ECUMaster Black + ESP32 Bluetooth Display

[![ESP32](https://img.shields.io/badge/board-ESP32-blue.svg)](https://www.espressif.com/en/products/socs/esp32)
[![ECUMaster](https://img.shields.io/badge/device-ECUMaster-black.svg)](https://www.ecumaster.com)
[![Bluetooth](https://img.shields.io/badge/communication-Bluetooth-brightgreen.svg)](https://en.wikipedia.org/wiki/Bluetooth)
[![LVGL](https://img.shields.io/badge/UI-LVGL-purple.svg)](https://lvgl.io/)
[![Arduino](https://img.shields.io/badge/framework-Arduino-blue.svg)](https://www.arduino.cc)
[![License: GPL v3](https://img.shields.io/badge/license-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0.en.html)
[![Language: C++](https://img.shields.io/badge/language-C++-orange.svg)](https://isocpp.org)

## 📦 Description

This project interfaces the **ECUMaster Black ECU** with an **ESP32** to create a Bluetooth-enabled dashboard display, featuring:

- Automatic Bluetooth reconnection
- Real-time monitoring of engine vitals
- Custom alerts (CEL, coolant temp, RPM, AFR, voltage, boost, etc.) via display & buzzer
- TFT screen GUI with **LVGL**

> ⚠️ **Note:** If `SerialBT.setPin(pin)` doesn't work, downgrade to **ESP32 Arduino Core 2.0.17** in the board manager.

## ✅ Tested On

- ESP32_3248S035C (or ESP32 JC2432W328  but need extra config...)
- Active 3.3V buzzer
- Arduino Core v2.0.17
- ECUMaster Black with Bluetooth Adapter and EDL-1
- LVGL v9.3

## 📥 Installation

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

## 📦 Dependencies

- [BluetoothSerial](https://github.com/espressif/arduino-esp32/tree/master/libraries/BluetoothSerial)
- [LVGL](https://lvgl.io)
- [eSPI](https://github.com/Bodmer/TFT_eSPI)

## 🧰 Hardware Used

- **ESP32_3248S035C**  
  [🛒 AliExpress link](https://www.aliexpress.com/w/wholesale-ESP32_3248S035C.html)
  
  [Documentation](https://drive.google.com/drive/folders/1Sk4sIXgLAqPZ03BzYb0IwUftMXJ9QMLN?usp=sharing)

- **ECU**  
[ECUMaster Black](https://www.ecumaster.com/products/emu-black/)

  [EMU CAN Bluetooth Adapter](https://ecumasterusa.com/products/bluetooth-adapter-for-ecumaster-emu-can-bus)

- **Active 3.3V buzzer**
 [🛒 AliExpress link](https://www.aliexpress.com/item/1005008682347898.html)
  


## 📜 License

This project is licensed under **GPL v3**.  
See the [LICENSE](https://www.gnu.org/licenses/gpl-3.0.en.html) file for more info.
