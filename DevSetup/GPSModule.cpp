#include "GPSModule.h"
#include "defs.h"

HardwareSerial gpsSerial(2);
TinyGPSPlus gps;

void gpsInit() {
  gpsSerial.begin(9600, SERIAL_8N1, GPS_RX, GPS_TX);
}

void updateGPS() {
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }
}
