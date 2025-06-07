#include "GPSModule.h"
#include "JPEGModule.h"
#include "CompassModule.h"
#include "BMEModule.h"
#include "GUIModule.h"

void setup() {
  Serial.begin(115200);
  guiInit();
  gpsInit();
  //jpegInit();
  //bmeInit();
  //compassInit();
}

void loop() {
  gpsUpdate();
  //compassUpdate();
  //bmeUpdate();
  guiUpdate();
  /*
  if (gps.location.isValid()) {
    double lat = gps.location.lat();
    double lng = gps.location.lng();
    int zoom = 16;
    //drawTileFromLocation(lat, lng, zoom);
  }
  */
  delay(1000);
}
