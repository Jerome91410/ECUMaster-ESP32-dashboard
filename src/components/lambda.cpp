#include "components.h"

lv_obj_t* ui_lambda = NULL;
lv_obj_t* ui_lambdaLabel = NULL;
lv_obj_t* ui_lambdaTarget = NULL;

void draw_lambda(lv_obj_t* ui_screen) {
  int offsetX = 170;
  int offsetY = 70;
  ui_lambdaLabel = lv_label_create(ui_screen);
  generic_text(ui_lambdaLabel, offsetX, offsetY, "lambda", &lv_font_montserrat_14);

  ui_lambda = lv_label_create(ui_screen);
  generic_text(ui_lambda, offsetX, offsetY + 10, "-", &lv_font_montserrat_48);

  ui_lambdaTarget = lv_label_create(ui_screen);
  generic_text(ui_lambdaTarget, offsetX + 110, offsetY + 20, "-", &lv_font_montserrat_18);
}

void set_lambda(EMUSerial emuSerial) {
  float wboLambda = emuSerial.emu_data.wboLambda;
  float lambdaTarget = emuSerial.emu_data.lambdaTarget;

  lv_label_set_text(ui_lambda, String(wboLambda).c_str());
  lv_label_set_text(ui_lambdaTarget, String(lambdaTarget).c_str());

  float delta = wboLambda / lambdaTarget;
  if (delta < 0.95) {
    // too enrich
    lv_obj_set_style_text_color(ui_lambda, lv_palette_main(LV_PALETTE_BLUE), LV_PART_MAIN | LV_STATE_DEFAULT);
  } else if (delta > 1.10) {
    lv_obj_set_style_text_color(ui_lambda, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN | LV_STATE_DEFAULT);
  } else if (delta > 1.05) {
    lv_obj_set_style_text_color(ui_lambda, lv_palette_main(LV_PALETTE_ORANGE), LV_PART_MAIN | LV_STATE_DEFAULT);
  } else {
    lv_obj_set_style_text_color(ui_lambda, lv_color_white(), LV_PART_MAIN | LV_STATE_DEFAULT);
  }
}

void destroy_lambda() {
  ui_lambda = NULL;
  ui_lambdaLabel = NULL;
  ui_lambdaTarget = NULL;
}