#include <Arduino.h>
#include <BluetoothSerial.h>
#include <TaskManagerIO.h>

#include <stdexcept>
#include <string>
using namespace std;

#include "EMUSerial.h"
#include "emu_mac_address.h"
#include "ledControl.h"
#include "my_config.h"
#include "ui.h"

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;
EMUSerial emuSerial;

const char *pin = "1234";
String myBtName = "ESP32-BT-Master";
uint8_t address[6] = {MAC0, MAC1, MAC2, MAC3, MAC4, MAC5};  // setup the value in lib/emu_mac_address.h
const int buzzerPin = 22;
bool buzzerOn = false;

const unsigned long reconnectInterval = 5000;
// Display & LVGL setup

void connectToBt() {
  bool connected;
  if (!SerialBT.hasClient()) {
    ledLightBlue();
    connected = SerialBT.connect(address);
    if (connected) {
      Serial.println("Connected Successfully!");
      ledBlue();
    } else {
      // reset values from emuSerial
      emuSerial.init();
      Serial.println("Initial connect failed. Will retry in loop...");
      ledRed();
      delay(1000);
    }
  }
}

void refreshLed() {
  if (!SerialBT.hasClient()) {
    ledBlinkBlue();
  } else {
    if (emuSerial.emu_data.cel > 0) {
      ledRed();
    } else {
      if (emuSerial.emu_data.RPM < SHIFTLIGHT_RPM_1) {
        ledBlue();
      } else if (emuSerial.emu_data.RPM > SHIFTLIGHT_RPM_2) {
        ledFastBlinkWhite();
      } else {
        ledWhite();
      }
    }
  }
}

void callbackReadBTData(const uint8_t *buffer, size_t size) {
  emuSerial.onReceive(buffer, size);
}

void refreshDisplay() {
  ui_Screen1_render(emuSerial);
}

void buzzAlarms() {
  float boost = (static_cast<float>(emuSerial.emu_data.MAP) / 100) - 1.0132f;
  buzzerOn = (emuSerial.emu_data.cel > 0 || emuSerial.emu_data.CLT > 105 || emuSerial.emu_data.RPM > 7000 || boost > 1.10 || (emuSerial.emu_data.Batt < 12.00 && emuSerial.emu_data.Batt > 1.00));
  digitalWrite(buzzerPin, (millis() % 600 < 300) && buzzerOn);
}

void loop() {
  taskManager.runLoop();
}

void setup() {
  // init Serial
  Serial.begin(115200);
  Serial.println("Serial init");
  Serial.printf("MAX_RPM: %d\n", MAX_RPM);
  Serial.printf("SHIFTLIGHT_RPM_1: %d\n", SHIFTLIGHT_RPM_1);
  Serial.printf("SHIFTLIGHT_RPM_2: %d\n", SHIFTLIGHT_RPM_2);

  // Init led
  initLed();
  ui_init();
  // init bluetooth
  SerialBT.begin(myBtName, true);
  SerialBT.setPin(pin);
  SerialBT.onData(callbackReadBTData);

  // init buzzer
  pinMode(buzzerPin, OUTPUT);

  // init tasks
  taskManager.yieldForMicros(100);
  taskManager.scheduleFixedRate(200, refreshLed);
  taskManager.scheduleFixedRate(100, refreshDisplay);
  taskManager.scheduleFixedRate(reconnectInterval, connectToBt);

#ifdef BUZZ_ALARM
  taskManager.scheduleFixedRate(300, buzzAlarms);
#endif
}
