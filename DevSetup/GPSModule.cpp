#include "GPSModule.h"
#include "defs.h"

HardwareSerial gpsSerial(2);
TinyGPSPlus gps;

void gpsInit() {
  gpsSerial.begin(9600, SERIAL_8N1, GPS_RX, GPS_TX);
}

double gpsLongitude() {
  if (gps.location.isValid()) {
    return gps.location.lng();
  } 
  return 0;
}

double gpsLatitude() {
  if (gps.location.isValid()) {
    return gps.location.lat();     
  } 
  return 0;
}

void gpsUpdate() {
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }
  
  Serial.print("Satellites: ");
  Serial.println(gps.satellites.value());

  if (gps.location.isValid()) {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);

    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);

    Serial.print("HDOP: ");
    Serial.println(gps.hdop.hdop());
  } else {
    Serial.println("Waiting for valid GPS fix...");
  }

}
