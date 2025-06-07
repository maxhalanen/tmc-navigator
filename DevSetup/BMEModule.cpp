#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>
#include <defs.h>

Adafruit_BME680 bme; //Initialize the BME680 as an object

float gasBaseline = 0;
bool baselineSet = false;

void bmeInit() {
  
  Wire.begin(SDA_PIN, SCL_PIN);
  
  if (!bme.begin(BME680_I2C_ADDRESS_GND)) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1);
  }
  
  bme.setTemperatureOversampling(BME680_OS_8X); //Takes the average of 8 sensor readings for Temperature oversampling
  bme.setPressureOversampling(BME680_OS_4X); //Average of 4 sensor readings for Pressure oversampling
  bme.setHumidityOversampling(BME680_OS_2X); //2 sensor readings for Humidity Oversampling
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3); // Digital filter of size 3 to smooth readings and reduce noise

  bme.setGasHeater(320, 150); // 320C for 150 ms GasHeater specific for the BME680 to determine air quality

  Serial.println("Sensor warming up and calibrating...");
  // Let the sensor warm up and stabilize for 10,000ms to get more accurate readings
  delay(10000); // 10,000ms = 10s
} 

void bmeUpdate() {
  if (!bme.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }
  
  Serial.print("Temperature: ");
  Serial.print(bme.temperature);
  Serial.println(" *C");
  
  Serial.print("Pressure: ");
  Serial.print(bme.pressure / 100.0);
  Serial.println(" hPa");
  
  Serial.print("Humidity: ");
  Serial.print(bme.humidity);
  Serial.println(" %");

  Serial.print("Gas Resistance: ");
  Serial.print(bme.gas_resistance / 1000.0);
  Serial.println(" KOhms");

  Serial.print("Air Quality: ");
  if (bme.gas_resistance < 5000) {
    Serial.println("Poor - High VOC levels");
  } else if (bme.gas_resistance < 50000) {
    Serial.println("Moderate");
  } else if (bme.gas_resistance < 100000) {
    Serial.println("Good");
  } else {
    Serial.println("Excellent - Low VOC levels");
  }
  
  Serial.println("-------------------");
  Serial.println(" ");
}