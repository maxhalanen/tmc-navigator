#include "GPSModule.h"
#include "JPEGModule.h"
#include "CompassModule.h"

void setup() {
  Serial.begin(115200);
  gpsInit();
  jpegInit();
  compassInit();
}

void loop() {
  updateGPS();
  updateCompass();

  if (gps.location.isValid()) {
    double lat = gps.location.lat();
    double lng = gps.location.lng();
    int zoom = 16;
    drawTileFromLocation(lat, lng, zoom);
  }
  delay(1000);
}
