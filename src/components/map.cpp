#include "components.h"

lv_obj_t* ui_map = NULL;
lv_obj_t* ui_mapLabel = NULL;
lv_obj_t* ui_mapUnit = NULL;

void draw_map(lv_obj_t* ui_screen) {
  int offsetX = 170;
  int offsetY = 135;
  ui_mapLabel = lv_label_create(ui_screen);
  generic_text(ui_mapLabel, offsetX, offsetY, "MAP", &lv_font_montserrat_14);

  ui_map = lv_label_create(ui_screen);
  generic_text(ui_map, offsetX, offsetY + 10, "-", &lv_font_montserrat_48);

  ui_mapUnit = lv_label_create(ui_screen);
  generic_text(ui_mapUnit, offsetX + 80, offsetY + 20, "kpa", &lv_font_montserrat_14);
}

void set_map(EMUSerial emuSerial) {
    lv_label_set_text(ui_map, String(emuSerial.emu_data.MAP).c_str());
}

void destroy_map() {
  ui_map = NULL;
  ui_mapUnit = NULL;
  ui_mapLabel = NULL;
}