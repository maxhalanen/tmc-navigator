#ifndef JPEG_MODULE_H
#define JPEG_MODULE_H

#include <TFT_eSPI.h>

void jpegInit();
void drawTileFromLocation(double lat, double lng, int zoom);
void drawSdJpeg(const char *filename, int xpos, int ypos);
void jpegRender(int xpos, int ypos);
void jpegInfo();
void showTime(uint32_t msTime);

#endif
