#ifndef _GEAR_H
#define _GEAR_H

#include "gear_font.h"

void draw_gear(lv_obj_t* ui_screen);
void set_gear(EMUSerial emuSerial);
void destroy_gear();
void set_gear_shiftAlert(bool isShiftExpected);

#endif