#include "components.h"
#include "ui.h"

lv_style_t style_rpmBar_redline;
lv_obj_t* ui_rpmScale = NULL;
lv_obj_t* ui_rpmbar = NULL;

void draw_rpmBar(lv_obj_t* ui_screen) {
  ui_rpmbar = lv_bar_create(ui_screen);
  lv_obj_set_size(ui_rpmbar, lv_pct(100), 60);
  lv_obj_set_y(ui_rpmbar, 0);
  lv_obj_set_x(ui_rpmbar, 0);
  lv_bar_set_range(ui_rpmbar, 0, 8000);
  lv_obj_set_style_radius(ui_rpmbar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(ui_rpmbar, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);

  lv_style_init(&style_rpmBar_redline);
  lv_style_set_bg_color(&style_rpmBar_redline, lv_palette_main(LV_PALETTE_RED));

  ui_rpmScale = lv_scale_create(ui_rpmbar);
  lv_obj_set_size(ui_rpmScale, lv_pct(102), 60);

  lv_scale_set_label_show(ui_rpmScale, true);
  lv_obj_center(ui_rpmScale);
  lv_obj_set_x(ui_rpmScale, 4);
  lv_obj_set_y(ui_rpmScale, 0);
  lv_scale_set_total_tick_count(ui_rpmScale, 41);
  lv_scale_set_major_tick_every(ui_rpmScale, 5);

  lv_obj_set_style_length(ui_rpmScale, 10, LV_PART_INDICATOR);
  lv_obj_set_style_length(ui_rpmScale, 5, LV_PART_ITEMS);
  lv_scale_set_range(ui_rpmScale, 0, 8000);

  static const char* custom_labels[] = {"", "1", "2", "3", "4", "5", "6", "7", NULL};
  lv_scale_set_text_src(ui_rpmScale, custom_labels);

  static lv_style_t indicator_style;
  lv_style_init(&indicator_style);

  /* Label style properties */
  lv_style_set_text_font(&indicator_style, &lv_font_montserrat_28);
  lv_style_set_text_color(&indicator_style, lv_palette_lighten(LV_PALETTE_BLUE, 5));

  /* Major tick properties */
  lv_style_set_line_color(&indicator_style, lv_palette_lighten(LV_PALETTE_BLUE, 5));
  lv_style_set_width(&indicator_style, 10U);     /*Tick length*/
  lv_style_set_line_width(&indicator_style, 2U); /*Tick width*/
  lv_obj_add_style(ui_rpmScale, &indicator_style, LV_PART_INDICATOR);

  static lv_style_t minor_ticks_style;
  lv_style_init(&minor_ticks_style);
  lv_style_set_line_color(&minor_ticks_style, lv_palette_lighten(LV_PALETTE_BLUE, 5));
  lv_style_set_width(&minor_ticks_style, 5U);      /*Tick length*/
  lv_style_set_line_width(&minor_ticks_style, 2U); /*Tick width*/
  lv_obj_add_style(ui_rpmScale, &minor_ticks_style, LV_PART_ITEMS);

  static lv_style_t main_line_style;
  lv_style_init(&main_line_style);
  /* Main line properties */
  lv_style_set_line_color(&main_line_style, lv_palette_lighten(LV_PALETTE_BLUE, 5));
  lv_style_set_line_width(&main_line_style, 4U);  // Tick width
  lv_obj_add_style(ui_rpmScale, &main_line_style, LV_PART_MAIN);

  /* Add a section */
  static lv_style_t section_minor_tick_style;
  static lv_style_t section_label_style;
  static lv_style_t section_main_line_style;

  lv_style_init(&section_label_style);
  lv_style_init(&section_minor_tick_style);
  lv_style_init(&section_main_line_style);

  /* Label style properties */
  lv_style_set_text_font(&section_label_style, &lv_font_montserrat_28);
  lv_style_set_text_color(&section_label_style, lv_palette_lighten(LV_PALETTE_RED, 2));
  lv_style_set_line_color(&section_label_style, lv_palette_lighten(LV_PALETTE_RED, 2));
  lv_style_set_line_width(&section_label_style, 5U); /*Tick width*/
  lv_style_set_line_color(&section_minor_tick_style, lv_palette_lighten(LV_PALETTE_RED, 3));
  lv_style_set_line_width(&section_minor_tick_style, 4U); /*Tick width*/
  /* Main line properties */
  lv_style_set_line_color(&section_main_line_style, lv_palette_lighten(LV_PALETTE_RED, 2));
  lv_style_set_line_width(&section_main_line_style, 4U); /*Tick width*/

  /* Configure section styles */
  lv_scale_section_t* section = lv_scale_add_section(ui_rpmScale);
  lv_scale_set_section_range(ui_rpmScale, section, 7000, 8000);
  lv_scale_set_section_style_indicator(ui_rpmScale, section, &section_label_style);
  lv_scale_set_section_style_items(ui_rpmScale, section, &section_minor_tick_style);
  lv_scale_set_section_style_main(ui_rpmScale, section, &section_main_line_style);
  lv_obj_set_style_pad_left(ui_rpmScale, 8, 0);
}

void set_rpm(EMUSerial emuSerial) {
  uint16_t RPM = emuSerial.emu_data.RPM;
  lv_bar_set_value(ui_rpmbar, RPM, LV_ANIM_ON);

  if (RPM <= SHIFTLIGHT_RPM_1) {
    tft.invertDisplay(false);
    lv_obj_remove_style(ui_rpmbar, &style_rpmBar_redline, LV_PART_INDICATOR);
#ifdef ESP32_3248S035C
    set_gear_shiftAlert(false);
#endif
  } else if (RPM > SHIFTLIGHT_RPM_1 && RPM < SHIFTLIGHT_RPM_2) {
    tft.invertDisplay(false);
    lv_obj_add_style(ui_rpmbar, &style_rpmBar_redline, LV_PART_INDICATOR);
#ifdef ESP32_3248S035C
    set_gear_shiftAlert(true);
#endif
  } else {
    tft.invertDisplay(true);
    lv_obj_add_style(ui_rpmbar, &style_rpmBar_redline, LV_PART_INDICATOR);
#ifdef ESP32_3248S035C
    set_gear_shiftAlert(true);
#endif
    lv_timer_handler();
    delay(5);
    lv_obj_remove_style(ui_rpmbar, &style_rpmBar_redline, LV_PART_INDICATOR);
#ifdef ESP32_3248S035C
    set_gear_shiftAlert(false);
#endif
  }
}

void destroy_rpm() {
  ui_rpmScale = NULL;
  ui_rpmbar = NULL;
}