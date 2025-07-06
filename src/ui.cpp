
#include "ui.h"

TFT_eSPI tft = TFT_eSPI();

// /*LVGL draw into this buffer, 1/10 screen size usually works well. The size is in bytes*/
#define DRAW_BUF_SIZE (TFT_HEIGHT * TFT_WIDTH / 10 * (LV_COLOR_DEPTH / 8))
uint16_t draw_buf[DRAW_BUF_SIZE / 4];

/* LVGL calls it when a rendered image needs to copied to the display*/
void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map) {
  /*Call it to tell LVGL you are ready*/
  lv_display_flush_ready(disp);
}

/*use Arduinos millis() as tick source*/
static uint32_t my_tick(void) {
  return millis();
}

void ui_init() {
  tft.init();
  tft.fillScreen(TFT_BLACK);
  lv_init();

  /*Set a tick source so that LVGL will know how much time elapsed. */
  lv_tick_set_cb(my_tick);

  lv_display_t *disp;
  /*TFT_eSPI can be enabled lv_conf.h to initialize the display in a simple way*/
  disp = lv_tft_espi_create(TFT_HEIGHT, TFT_WIDTH, draw_buf, sizeof(draw_buf));

#ifdef ESP32_3248S035C
  // if 3.5", it s required to invert the display, otherwise it s inverted

  tft.writecommand(TFT_MADCTL);
  tft.writedata(TFT_MAD_MV | TFT_MAD_BGR);
#endif

#ifdef JC2432W328
  tft.writecommand(TFT_MADCTL);
  tft.writedata(TFT_MAD_MV | TFT_MAD_BGR);
  // TODO: need to fix it
  //  currently the screen is mirrored...
  // May remove the support of this device as it s way too small to display enough readable data
#endif

  lv_disp_t *dispp = lv_disp_get_default();
  lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                            false, LV_FONT_DEFAULT);
  lv_disp_set_theme(dispp, theme);
  ui_Screen1_screen_init();

  lv_disp_load_scr(ui_Screen1);
}

void ui_destroy(void) {
  ui_Screen1_screen_destroy();
}
