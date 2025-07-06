#ifndef _UI_H
#define _UI_H
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <lvgl.h>

///////////////////// SCREENS ////////////////////

#include "ui_Screen1.h"

///////////////////// VARIABLES ////////////////////

extern TFT_eSPI tft;

// UI INIT
void ui_init(void);
void ui_destroy(void);

#endif
