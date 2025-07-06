#include "components.h"

void generic_text(lv_obj_t* obj, int x, int y, const char* text, const lv_font_t* font) {
  lv_obj_set_width(obj, LV_SIZE_CONTENT);
  lv_obj_set_height(obj, LV_SIZE_CONTENT);
  lv_obj_set_x(obj, x);
  lv_obj_set_y(obj, y);
  lv_obj_set_align(obj, LV_ALIGN_TOP_LEFT);
  lv_label_set_text(obj, text);
  lv_obj_set_style_text_color(obj, lv_color_white(), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(obj, font, LV_PART_MAIN | LV_STATE_DEFAULT);
}
