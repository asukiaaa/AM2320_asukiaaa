#include <AM2320_asukiaaa.h>

AM2320_asukiaaa mySensor;

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial.println("started");
  Wire.begin();
  mySensor.setWire(&Wire);
}

void loop() {
  if (mySensor.update() != 0) {
    Serial.println("Error: Cannot update sensor values.");
  } else {
    Serial.println("temperatureC: " + String(mySensor.temperatureC) + " C");
    Serial.println("temperatureF: " + String(mySensor.temperatureF) + " F");
    Serial.println("humidity: " + String(mySensor.humidity) + " %");
  }
  Serial.println("at " + String(millis()) + " ms");
  Serial.println("");
  delay(500);
}
