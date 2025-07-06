#include "components.h"

lv_obj_t* ui_cel = NULL;
lv_obj_t* ui_celLabel = NULL;
lv_obj_t* ui_celUnit = NULL;

void draw_cel(lv_obj_t* ui_screen) {
  int offsetX = 170;
  int offsetY = 265;
  ui_celLabel = lv_label_create(ui_screen);
  generic_text(ui_celLabel, offsetX, offsetY, "CEL", &lv_font_montserrat_14);

  ui_cel = lv_label_create(ui_screen);
  generic_text(ui_cel, offsetX, offsetY + 10, "-", &lv_font_montserrat_48);
}

void set_cel(EMUSerial emuSerial) {
  if (emuSerial.isCelOn()) {
    lv_obj_set_style_text_color(ui_cel, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(ui_cel, emuSerial.decodeCel().c_str());
  } else {
    lv_obj_set_style_text_color(ui_cel, lv_color_white(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(ui_cel, "-");
  }
}

void destroy_cel() {
  ui_cel = NULL;
  ui_celUnit = NULL;
  ui_celLabel = NULL;
}