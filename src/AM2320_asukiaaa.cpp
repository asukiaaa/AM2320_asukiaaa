#include "AM2320_asukiaaa.h"

uint16_t CRC16(uint8_t *ptr, uint8_t length) {
  uint16_t crc = 0xFFFF;
  uint8_t s = 0x00;

  while(length--) {
    crc ^= *ptr++;
    for(s = 0; s < 8; s++) {
      if((crc & 0x01) != 0) {
        crc >>= 1;
        crc ^= 0xA001;
      } else crc >>= 1;
    }
  }
  return crc;
}

AM2320_asukiaaa::AM2320_asukiaaa() {
  myWire = &Wire;
}

void AM2320_asukiaaa::setWire(TwoWire* wire) {
  myWire = wire;
}

int AM2320_asukiaaa::update() {
  static const int buffLen = 8;
  uint8_t buf[buffLen];

  // Wakeup sensor
  myWire->beginTransmission(AM2320_asukiaaa_DEVICE_ADDRESS);
  myWire->endTransmission(); // Don't use value of endTransmission on this time because it returns error when the sensor slept.
  delay(10);

  myWire->beginTransmission(AM2320_asukiaaa_DEVICE_ADDRESS);
  myWire->write((unsigned char) 0x03);
  myWire->write((unsigned char) 0x00);
  myWire->write((unsigned char) 0x04);
  int result = myWire->endTransmission();
  if (result != AM2320_asukiaaa_SUCCESS) return result;
  delay(2); // >1.5ms
  myWire->requestFrom(AM2320_asukiaaa_DEVICE_ADDRESS, buffLen);
  for (uint8_t i = 0; i < buffLen; ++i) {
    buf[i] = myWire->read();
  }

  // Fusion Code check
  if (buf[0] != 0x03) return AM2320_asukiaaa_ERROR_FUSION_CODE_UNMATCH;

  // CRC check
  uint16_t Rcrc = buf[7] << 8;
  Rcrc += buf[6];
  if (Rcrc != CRC16(buf, 6)) return AM2320_asukiaaa_ERROR_CRC_UNMATCH;

  uint16_t t = (((uint16_t) buf[4] & 0x7F) << 8) | buf[5];
  temperatureC = t / 10.0;
  temperatureC = ((buf[4] & 0x80) >> 7) == 1 ? temperatureC * (-1) : temperatureC;
  temperatureF = temperatureC * 9 / 5 + 32;

  uint16_t h = ((uint16_t) buf[2] << 8) | buf[3];
  humidity = h / 10.0;

  return AM2320_asukiaaa_SUCCESS;
}
