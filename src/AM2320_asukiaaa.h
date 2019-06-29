#ifndef AM2320_ASUKIAAA_H
#define AM2320_ASUKIAAA_H

#include <Arduino.h>
#include <Wire.h>

#define AM2320_ADDRESS 0x5C // (0xB8 >> 1)

class AM2320_asukiaaa {
  public:
  enum Errors {
    SUCCESS = 0,
    WIRE_DATA_TOO_LONG = 1,
    WIRE_RECEIVED_NACK_OF_ADDRESS = 2,
    WIRE_RECEIVED_NACK_OF_DATA = 3,
    WIRE_OTHER_ERROR = 4,
    FUSION_CODE_UNMATCH = 5,
    CRC_UNMATCH = 6,
  };

  AM2320_asukiaaa();
  void setWire(TwoWire *wire);
  Errors update();
  float temperatureC;
  float temperatureF;
  float humidity;

  private:
  TwoWire* myWire;
};

#endif
