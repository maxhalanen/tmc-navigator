#ifndef GPS_MODULE_H
#define GPS_MODULE_H

#include <TinyGPS++.h>
#include <HardwareSerial.h>

extern TinyGPSPlus gps;

void gpsInit();
void updateGPS();

#endif
