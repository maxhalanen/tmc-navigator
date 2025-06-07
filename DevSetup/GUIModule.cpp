/*  Rui Santos & Sara Santos - Random Nerd Tutorials
    THIS EXAMPLE WAS TESTED WITH THE FOLLOWING HARDWARE:
    1) ESP32-2432S028R 2.8 inch 240×320 also known as the Cheap Yellow Display (CYD): https://makeradvisor.com/tools/cyd-cheap-yellow-display-esp32-2432s028r/
      SET UP INSTRUCTIONS: https://RandomNerdTutorials.com/cyd-lvgl/
    2) REGULAR ESP32 Dev Board + 2.8 inch 240x320 TFT Display: https://makeradvisor.com/tools/2-8-inch-ili9341-tft-240x320/ and https://makeradvisor.com/tools/esp32-dev-board-wi-fi-bluetooth/
      SET UP INSTRUCTIONS: https://RandomNerdTutorials.com/esp32-tft-lvgl/
    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*/
#include "GUIModule.h"
#include "gpsModule.h"
/*  Install the "lvgl" library version 9.2 by kisvegabor to interface with the TFT Display - https://lvgl.io/
    *** IMPORTANT: lv_conf.h available on the internet will probably NOT work with the examples available at Random Nerd Tutorials ***
    *** YOU MUST USE THE lv_conf.h FILE PROVIDED IN THE LINK BELOW IN ORDER TO USE THE EXAMPLES FROM RANDOM NERD TUTORIALS ***
    FULL INSTRUCTIONS AVAILABLE ON HOW CONFIGURE THE LIBRARY: https://RandomNerdTutorials.com/cyd-lvgl/ or https://RandomNerdTutorials.com/esp32-tft-lvgl/   */

/*  Install the "TFT_eSPI" library by Bodmer to interface with the TFT Display - https://github.com/Bodmer/TFT_eSPI
    *** IMPORTANT: User_Setup.h available on the internet will probably NOT work with the examples available at Random Nerd Tutorials ***
    *** YOU MUST USE THE User_Setup.h FILE PROVIDED IN THE LINK BELOW IN ORDER TO USE THE EXAMPLES FROM RANDOM NERD TUTORIALS ***
    FULL INSTRUCTIONS AVAILABLE ON HOW CONFIGURE THE LIBRARY: https://RandomNerdTutorials.com/cyd-lvgl/ or https://RandomNerdTutorials.com/esp32-tft-lvgl/   */
#include <TFT_eSPI.h>

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320
#define DRAW_BUF_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))

uint32_t draw_buf[DRAW_BUF_SIZE / 4];

lv_obj_t* label1 = NULL; // Latitude label
lv_obj_t* label2 = NULL; // Longitude label

// If logging is enabled, it will inform the user about what is happening in the library
void log_print(lv_log_level_t level, const char * buf) {
  LV_UNUSED(level);
  Serial.println(buf);
  Serial.flush();
}
void lv_create_main_gui(void) {
  // Set screen background
  lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x393E46), LV_PART_MAIN);
  lv_obj_set_style_bg_opa(lv_scr_act(), LV_OPA_COVER, LV_PART_MAIN);

  // Bubble 1 for latitude
  lv_obj_t* bubble1 = lv_obj_create(lv_scr_act());
  lv_obj_set_size(bubble1, 100, 40);
  lv_obj_set_style_radius(bubble1, LV_RADIUS_CIRCLE, 1); 
  lv_obj_set_style_bg_color(bubble1, lv_color_hex(0x222831), LV_PART_MAIN); 
  lv_obj_set_style_pad_all(bubble1, 8, LV_PART_MAIN);
  lv_obj_set_pos(bubble1, 20, 30);  

  label1 = lv_label_create(bubble1); // Store globally
  lv_label_set_text(label1, "Lat: ...");
  lv_obj_set_style_text_color(label1, lv_color_hex(0xFFFFFF), LV_PART_MAIN);

  // Bubble 2 for longitude
  lv_obj_t* bubble2 = lv_obj_create(lv_scr_act());
  lv_obj_set_size(bubble2, 100, 40);
  lv_obj_set_style_radius(bubble2, LV_RADIUS_CIRCLE, 1); 
  lv_obj_set_style_bg_color(bubble2, lv_color_hex(0x222831), LV_PART_MAIN); 
  lv_obj_set_style_pad_all(bubble2, 8, LV_PART_MAIN);
  lv_obj_set_pos(bubble2, 150, 30);  

  label2 = lv_label_create(bubble2); // Store globally
  lv_label_set_text(label2, "Lng: ...");
  lv_obj_set_style_text_color(label2, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
}


void guiInit() {

  String LVGL_Arduino = String("LVGL Library Version: ") + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();
  Serial.println(LVGL_Arduino);

  // Start LVGL
  lv_init();

  // Register print function for debugging
  lv_log_register_print_cb(log_print);

  // Create a display object
  lv_display_t * disp;

  // Initialize the TFT display using the TFT_eSPI library
  disp = lv_tft_espi_create(SCREEN_WIDTH, SCREEN_HEIGHT, draw_buf, sizeof(draw_buf));
  lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_270);



  // Function to draw the GUI (text, buttons and sliders)
  lv_create_main_gui();
}


void guiUpdate() {
  static unsigned long lastUpdate = 0;
  unsigned long now = millis();

  lv_task_handler();  // Let LVGL process UI
  lv_tick_inc(5);
  delay(5);

  // Update GPS values every 500ms
  if (now - lastUpdate > 500) {
    lastUpdate = now;

    double lat = gpsLatitude();
    double lng = gpsLongitude();

    char buffer_1[32];
    snprintf(buffer_1, sizeof(buffer_1), "Lat: %.6f", lat);
    lv_label_set_text(label1, buffer_1);

    char buffer_2[32];
    snprintf(buffer_2, sizeof(buffer_2), "Lng: %.6f", lng);
    lv_label_set_text(label2, buffer_2);
  }
}