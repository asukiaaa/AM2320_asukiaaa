#ifndef AM2320_ASUKIAAA_H
#define AM2320_ASUKIAAA_H

#define AM2320_asukiaaa_DEVICE_ADDRESS 0x5C // (0xB8 >> 1)

#define AM2320_asukiaaa_SUCCESS                             0
#define AM2320_asukiaaa_ERROR_WIRE_DATA_TOO_LONG            1
#define AM2320_asukiaaa_ERROR_WIRE_RECEIVED_NACK_OF_ADDRESS 2
#define AM2320_asukiaaa_ERROR_WIRE_RECEIVED_NACK_OF_DATA    3
#define AM2320_asukiaaa_ERROR_WIRE_OTHER_ERROR              4
#define AM2320_asukiaaa_ERROR_FUSION_CODE_UNMATCH           5
#define AM2320_asukiaaa_ERROR_CRC_UNMATCH                   6

#include <Arduino.h>
#include <Wire.h>

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
