#ifndef UI_SCREEN1_H
#define UI_SCREEN1_H

#include "EMUSerial.h"
#include "my_config.h"

extern lv_obj_t* ui_Screen1;

extern lv_obj_t* ui_rpmLabel;
extern lv_obj_t* ui_lambdaLabel;
extern lv_obj_t* ui_lambdaValue;
extern lv_obj_t* ui_ltLabel;
extern lv_obj_t* ui_lambdaTargetValue;
extern lv_obj_t* ui_mapLabel;
extern lv_obj_t* ui_mapValue;

void ui_Screen1_screen_init(void);
void ui_Screen1_render(EMUSerial emuSerial);
void ui_Screen1_screen_destroy(void);

#endif
