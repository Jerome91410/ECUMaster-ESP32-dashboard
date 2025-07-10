#include "components.h"

lv_obj_t* ui_intakeAirTemp = NULL;
lv_obj_t* ui_intakeAirTempLabel = NULL;
lv_obj_t* ui_intakeAirTempUnit = NULL;

void draw_intakeAirTemp(lv_obj_t* ui_screen) {
  int offsetX = 15;
  int offsetY = 265;
  ui_intakeAirTempLabel = lv_label_create(ui_screen);
  generic_text(ui_intakeAirTempLabel, offsetX, offsetY, "IAT", &lv_font_montserrat_14);

  ui_intakeAirTemp = lv_label_create(ui_screen);
  generic_text(ui_intakeAirTemp, offsetX, offsetY + 10, "-", &lv_font_montserrat_48);

  ui_intakeAirTempUnit = lv_label_create(ui_screen);
  generic_text(ui_intakeAirTempUnit, offsetX + 80, offsetY + 20, "°C", &lv_font_montserrat_14);
}

void set_intakeAirTemp(EMUSerial emuSerial) {
  int8_t IAT = emuSerial.emu_data.IAT;

  lv_label_set_text(ui_intakeAirTemp, String(IAT).c_str());
  if (IAT > 55) {
    lv_obj_set_style_text_color(ui_intakeAirTemp, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN | LV_STATE_DEFAULT);
  } else {
    lv_obj_set_style_text_color(ui_intakeAirTemp, lv_color_white(), LV_PART_MAIN | LV_STATE_DEFAULT);
  }
}

void destroy_intakeAirTemp() {
  ui_intakeAirTemp = NULL;
  ui_intakeAirTempUnit = NULL;
  ui_intakeAirTempLabel = NULL;
}