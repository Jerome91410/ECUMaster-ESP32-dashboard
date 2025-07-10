#include "components.h"

lv_obj_t* ui_oilTemp = NULL;
lv_obj_t* ui_oilTempLabel = NULL;
lv_obj_t* ui_oilTempUnit = NULL;

void draw_oilTemp(lv_obj_t* ui_screen) {
  int offsetX = 15;
  int offsetY = 135;
  ui_oilTempLabel = lv_label_create(ui_screen);
  generic_text(ui_oilTempLabel, offsetX, offsetY, "Oil Temp", &lv_font_montserrat_14);

  ui_oilTemp = lv_label_create(ui_screen);
  generic_text(ui_oilTemp, offsetX, offsetY + 10, "-", &lv_font_montserrat_48);

  ui_oilTempUnit = lv_label_create(ui_screen);
  generic_text(ui_oilTempUnit, offsetX + 80, offsetY + 20, "°C", &lv_font_montserrat_14);
}

void set_oilTemp(EMUSerial emuSerial) {
  uint8_t oilTemperature = emuSerial.emu_data.oilTemperature;
  lv_label_set_text(ui_oilTemp, String(oilTemperature).c_str());
  if (oilTemperature < 90 && oilTemperature > 0) {
    lv_obj_set_style_text_color(ui_oilTemp, lv_palette_main(LV_PALETTE_BLUE), LV_PART_MAIN | LV_STATE_DEFAULT);
  } else if (oilTemperature > 115) {
    lv_obj_set_style_text_color(ui_oilTemp, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN | LV_STATE_DEFAULT);
  } else {
    lv_obj_set_style_text_color(ui_oilTemp, lv_color_white(), LV_PART_MAIN | LV_STATE_DEFAULT);
  }
}

void destroy_oilTemp() {
  ui_oilTemp = NULL;
  ui_oilTempUnit = NULL;
  ui_oilTempLabel = NULL;
}