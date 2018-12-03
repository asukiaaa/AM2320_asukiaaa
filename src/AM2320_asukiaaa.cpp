#include "AM2320_asukiaaa.h"

unsigned int CRC16(byte *ptr, unsigned int length) {
  unsigned int crc = 0xFFFF;
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

AM2320::AM2320() {}

void AM2320::setWire(TwoWire* wire) {
  myWire = wire;
}

int AM2320::update() {
  byte buf[8];
  for(int s = 0; s < 8; s++) buf[s] = 0x00;

  myWire->beginTransmission(AM2320_ADDRESS);
  myWire->endTransmission();
  delay(10);
  myWire->beginTransmission(AM2320_ADDRESS);
  myWire->write(0x03);
  myWire->write(0x00);
  myWire->write(0x04);
  if (myWire->endTransmission(true) != 0) {
    return 1;
  }
  delayMicroseconds(1600); // >1.5ms
  myWire->requestFrom(AM2320_ADDRESS, 0x08);
  for (int i = 0; i < 0x08; i++) {
    buf[i] = myWire->read();
  }

  // Fusion Code check
  if (buf[0] != 0x03) return 2;

  // CRC check
  unsigned int Rcrc = buf[7] << 8;
  Rcrc += buf[6];
  if (Rcrc != CRC16(buf, 6)) return 2;

  unsigned int t = ((buf[4] & 0x7F) << 8) + buf[5];
  temperatureC = t / 10.0;
  temperatureC = ((buf[4] & 0x80) >> 7) == 1 ? temperatureC * (-1) : temperatureC;
  temperatureF = temperatureC * 9 / 5 + 32;

  unsigned int h = (buf[2] << 8) + buf[3];
  humidity = h / 10.0;

  return 0;
}
