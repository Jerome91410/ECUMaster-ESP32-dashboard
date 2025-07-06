#include "components.h"

lv_obj_t* ui_gear = NULL;

void draw_gear(lv_obj_t* ui_screen) {
  ui_gear = lv_label_create(ui_screen);
  generic_text(ui_gear, 360, 100, "-", &gear_font);
  lv_obj_set_style_text_color(ui_gear, lv_color_hex(0xFFDB00), LV_PART_MAIN | LV_STATE_DEFAULT);
}

void set_gear_shiftAlert(bool isShiftExpected) {
  if (isShiftExpected) {
    lv_obj_set_style_text_color(ui_gear, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN | LV_STATE_DEFAULT);
  } else {
    lv_obj_set_style_text_color(ui_gear, lv_color_hex(0xFFDB00), LV_PART_MAIN | LV_STATE_DEFAULT);
  }
}

void set_gear(EMUSerial emuSerial) {
  int8_t gear = emuSerial.emu_data.gear;
  if (gear <= 0) return;
  lv_label_set_text(ui_gear, String(gear).c_str());
}

void destroy_gear() {
  ui_gear = NULL;
}