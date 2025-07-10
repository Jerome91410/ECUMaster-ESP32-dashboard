
#include "components.h"
#include "ui.h"

lv_obj_t* ui_Screen1 = NULL;

void ui_Screen1_screen_init(void) {
  ui_Screen1 = lv_obj_create(NULL);
  lv_obj_set_style_bg_color(ui_Screen1, lv_color_make(30, 30, 30), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Screen1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

  // render components
  draw_oilTemp(ui_Screen1);
  draw_oilPressure(ui_Screen1);
  draw_waterTemp(ui_Screen1);
  draw_lambda(ui_Screen1);
  draw_map(ui_Screen1);
  draw_cel(ui_Screen1);
  draw_rpmBar(ui_Screen1);
#ifndef JC2432W328
  draw_gear(ui_Screen1);
  draw_knockCount(ui_Screen1);
  draw_intakeAirTemp(ui_Screen1);
#endif
}

void ui_Screen1_screen_destroy(void) {
  if (ui_Screen1) lv_obj_del(ui_Screen1);

  // NULL screen variables
  ui_Screen1 = NULL;
  destroy_rpm();
  destroy_oilTemp();
  destroy_waterTemp();
  destroy_oilPressure();
  destroy_lambda();
  destroy_map();
  destroy_cel();

#ifndef JC2432W328
  destroy_gear();
  destroy_knockCount();
  destroy_intakeAirTemp();
#endif
}

int32_t rpm = 1500;
int32_t inc = 10;
int32_t gear = 1;

void ui_Screen1_render(EMUSerial emuSerial) {
  rpm += inc;

  set_oilPressure(emuSerial);
  set_oilTemp(emuSerial);
  set_rpm(emuSerial);
  set_waterTemp(emuSerial);
  set_lambda(emuSerial);
  set_map(emuSerial);
  set_cel(emuSerial);

#ifndef JC2432W328
  set_gear(emuSerial);
  set_knockCount(emuSerial);
  set_intakeAirTemp(emuSerial);
#endif

  // reset
  if (rpm > MAX_RPM) {
    gear++;
    rpm = 1400;
  }
  if (gear > 6) gear = 1;
  lv_timer_handler();
}