#include "components.h"

lv_obj_t* ui_waterTemp = NULL;
lv_obj_t* ui_waterTempLabel = NULL;
lv_obj_t* ui_waterTempUnit = NULL;

void draw_waterTemp(lv_obj_t* ui_screen) {
  int offsetX = 15;
  int offsetY = 200;
  ui_waterTempLabel = lv_label_create(ui_screen);
  generic_text(ui_waterTempLabel, offsetX, offsetY, "CLT", &lv_font_montserrat_14);

  ui_waterTemp = lv_label_create(ui_screen);
  generic_text(ui_waterTemp, offsetX, offsetY + 10, "-", &lv_font_montserrat_48);

  ui_waterTempUnit = lv_label_create(ui_screen);
  generic_text(ui_waterTempUnit, offsetX + 80, offsetY + 20, "°C", &lv_font_montserrat_14);
}

void set_waterTemp(EMUSerial emuSerial) {
  int16_t CLT = emuSerial.emu_data.CLT;
  lv_label_set_text(ui_waterTemp, String(CLT).c_str());
  if (CLT < 70 && CLT > 0) {
    lv_obj_set_style_text_color(ui_waterTemp, lv_palette_main(LV_PALETTE_BLUE), LV_PART_MAIN | LV_STATE_DEFAULT);
  } else if (CLT > 95) {
    lv_obj_set_style_text_color(ui_waterTemp, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN | LV_STATE_DEFAULT);
  } else {
    lv_obj_set_style_text_color(ui_waterTemp, lv_color_white(), LV_PART_MAIN | LV_STATE_DEFAULT);
  }
}

void destroy_waterTemp() {
  ui_waterTemp = NULL;
  ui_waterTempUnit = NULL;
  ui_waterTempLabel = NULL;
}