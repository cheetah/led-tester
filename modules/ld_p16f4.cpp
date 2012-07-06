#include "ld_p16f4.h"

ld_p16f4::ld_p16f4() {
  Led::SetConfiguration(Led::Out);
}

ld_p16f4::~ld_p16f4() {
  Led::Write<0>();
}

void ld_p16f4::enable() {
  PinOE::Clear();
}

void ld_p16f4::disable() {
  PinOE::Set();
}

void ld_p16f4::shift(uint8_t state) {
  int i;

  switch(state) {
    case 0:
      LedData::Write<0>();     // 0b000000xxx
      break;

    case 1:
      LedData::Write<0x18>();  // 0b000011xxx    
      break;

    case 2:
      LedData::Write<0x60>(); // 0b001100xxx
      break;

    case 3:
      LedData::Write<0x78>(); // 0b001111xxx
      break;

    case 4:
      LedData::Write<0x180>(); // 0b110000xxx
      break;

    case 5:
      LedData::Write<0x198>(); // 0b110011xxx
      break;

    case 6:
      LedData::Write<0x1E0>(); // 0b111100xxx
      break;

    case 7:
      LedData::Write<0x1F8>(); // 0b111111xxx
      break;

  }

  for(i = 0; i < 64; i++) {
    PinCLK::Set();
    PinCLK::Clear();
  }

  PinLAT::Set();
  PinLAT::Clear();
}

void ld_p16f4::test() {
  _delay_ms(5);
}