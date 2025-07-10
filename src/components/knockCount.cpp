#include "components.h"

lv_obj_t* ui_knockCount = NULL;
lv_obj_t* ui_knockCountLabel = NULL;
lv_obj_t* ui_knockCountUnit = NULL;

void draw_knockCount(lv_obj_t* ui_screen) {
  int offsetX = 170;
  int offsetY = 200;
  ui_knockCountLabel = lv_label_create(ui_screen);
  generic_text(ui_knockCountLabel, offsetX, offsetY, "Knocks", &lv_font_montserrat_14);

  ui_knockCount = lv_label_create(ui_screen);
  generic_text(ui_knockCount, offsetX, offsetY + 10, "-", &lv_font_montserrat_48);
}

void set_knockCount(EMUSerial emuSerial) {
  uint16_t knockCount = emuSerial.emu_data.knockCount;

  lv_label_set_text(ui_knockCount, String(knockCount).c_str());
  if (knockCount > 0) {
    lv_obj_set_style_text_color(ui_knockCount, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN | LV_STATE_DEFAULT);
  }
}

void destroy_knockCount() {
  ui_knockCount = NULL;
  ui_knockCountUnit = NULL;
  ui_knockCountLabel = NULL;
}