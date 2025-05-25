#include "GPSModule.h"
#include "JPEGModule.h"

void setup() {
  Serial.begin(115200);
  gpsInit();
  jpegInit();
}

void loop() {
  updateGPS();
  if (gps.location.isValid()) {
    double lat = gps.location.lat();
    double lng = gps.location.lng();
    int zoom = 16;
    drawTileFromLocation(lat, lng, zoom);
  }
  delay(1000);
}
