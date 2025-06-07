#ifndef GUI_MODULE_H
#define GUI_MODULE_H

#include <lvgl.h>

void log_print(lv_log_level_t level, const char * buf);
void lv_create_main_gui(void);
void guiInit();
void guiUpdate();

#endif