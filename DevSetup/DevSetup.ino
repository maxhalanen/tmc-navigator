#include "GPSModule.h"
#include "JPEGModule.h"
#include "CompassModule.h"
#include "BMEModule.h"

void setup() {
  Serial.begin(115200);
  gpsInit();
  jpegInit();
  bmeInit();
  compassInit();
}

void loop() {
  updateGPS();
  updateCompass();
  updateBME();

  if (gps.location.isValid()) {
    double lat = gps.location.lat();
    double lng = gps.location.lng();
    int zoom = 16;
    drawTileFromLocation(lat, lng, zoom);
  }
  delay(1000);
}
