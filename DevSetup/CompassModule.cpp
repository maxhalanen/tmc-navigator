#include "CompassModule.h"
#include <Adafruit_MMC56x3.h>
#include "defs.h"

/* Assign a unique ID to this sensor at the same time */
Adafruit_MMC5603 mmc = Adafruit_MMC5603(12345);

void compassInit() {

  Serial.println("Adafruit_MMC5603 Magnetometer Test");
  Serial.println("");

  Wire.begin(SDA_PIN, SCL_PIN);
  /* Initialise the sensor */
  if (!mmc.begin(MMC56X3_DEFAULT_ADDRESS, &Wire)) {  // I2C mode
    /* There was a problem detecting the MMC5603 ... check your connections */
    Serial.println("Ooops, no MMC5603 detected ... Check your wiring!");
    //while (1) delay(10);
  }

  /* Display some basic information on this sensor */
  mmc.printSensorDetails();
}

void compassUpdate() {
  // Get a new sensor event 
  sensors_event_t event;
  mmc.getEvent(&event);

  // Display the results (magnetic vector values are in micro-Tesla (uT))
  Serial.print("X: ");
  Serial.print(event.magnetic.x);
  Serial.print("  ");
  Serial.print("Y: ");
  Serial.print(event.magnetic.y);
  Serial.print("  ");
  Serial.print("Z: ");
  Serial.print(event.magnetic.z);
  Serial.print("  ");
  Serial.println("uT");

  // Read and display temperature
  float temp_c = mmc.readTemperature();
  Serial.print("Temp: "); 
  Serial.print(temp_c); 
  Serial.println(" *C");
}