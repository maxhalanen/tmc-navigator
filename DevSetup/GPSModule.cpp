#include "GPSModule.h"

HardwareSerial gpsSerial(2);
TinyGPSPlus gps;

void gpsInit() {
  gpsSerial.begin(9600, SERIAL_8N1, 16, 17);
}

void updateGPS() {
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }
}
