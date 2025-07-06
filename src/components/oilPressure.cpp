#include "components.h"

lv_obj_t* ui_oilPressure = NULL;
lv_obj_t* ui_oilPressureLabel = NULL;
lv_obj_t* ui_oilPressureUnit = NULL;

void draw_oilPressure(lv_obj_t* ui_screen) {
  int offsetX = 15;
  int offsetY = 70;
  ui_oilPressureLabel = lv_label_create(ui_screen);
  generic_text(ui_oilPressureLabel, offsetX, offsetY, "Oil Pressure", &lv_font_montserrat_14);

  ui_oilPressure = lv_label_create(ui_screen);
  generic_text(ui_oilPressure, offsetX, offsetY + 10, "-", &lv_font_montserrat_48);

  ui_oilPressureUnit = lv_label_create(ui_screen);
  generic_text(ui_oilPressureUnit, offsetX + 80, offsetY + 20, "bar", &lv_font_montserrat_14);
}

void set_oilPressure(EMUSerial emuSerial) {
  char buffer[4];
  snprintf(buffer, 4, "%'.1f", emuSerial.emu_data.oilPressure);
  lv_label_set_text(ui_oilPressure, String(buffer).c_str());
}

void destroy_oilPressure() {
  ui_oilPressure = NULL;
  ui_oilPressureUnit = NULL;
  ui_oilPressureLabel = NULL;
}