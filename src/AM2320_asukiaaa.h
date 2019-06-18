#ifndef AM2320_ASUKIAAA_H
#define AM2320_ASUKIAAA_H

#include <Arduino.h>
#include <Wire.h>

#define AM2320_ADDRESS 0x5C // (0xB8 >> 1)

class AM2320_asukiaaa {
  public:
  AM2320_asukiaaa();
  void setWire(TwoWire *wire);
  int update();
  float temperatureC;
  float temperatureF;
  float humidity;

  private:
  TwoWire* myWire;
};

#endif
