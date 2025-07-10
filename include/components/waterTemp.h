#ifndef _WATER_TEMP_H
#define _WATER_TEMP_H

void draw_waterTemp(lv_obj_t* ui_screen);
void set_waterTemp(EMUSerial emuSerial);
void destroy_waterTemp();

#endif