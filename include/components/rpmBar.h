#ifndef _RPM_BAR_H
#define _RPM_BAR_H

void draw_rpmBar(lv_obj_t* ui_screen);
void set_rpm(EMUSerial emuSerial);
void destroy_rpm();

#endif