#ifndef _INTAKE_AIR_TEMP_H
#define _INTAKE_AIR_TEMP_H

void draw_intakeAirTemp(lv_obj_t* ui_screen);
void set_intakeAirTemp(EMUSerial emuSerial);
void destroy_intakeAirTemp();

#endif