#include "leder_3ini.h"

void leder_3ini::init() {
  Led::SetConfiguration(Led::Out);

  PWM::SetConfiguration(PWM::Port::Out);

  Timer1::Start(Timer1::Div1);
  Timer1::SetMode(Timer1::ClearOnMatchOcr1a);
  TCCR1A |= ((0 << COM1B1) | (1 << COM1B0));
}

void leder_3ini::enable() {
  PinCON::Clear();
}

void leder_3ini::disable() {
  PinCON::Set();
}

void leder_3ini::shift(uint8_t state) {
  int i, j, k;

  switch(state) {
    case 0:
      LedData::Write<0>();     // 0b000000xxxxxx
      break;

    case 1:
      LedData::Write<0xC0>();  // 0b000011xxxxxx     
      break;

    case 2:
      LedData::Write<0x300>(); // 0b001100xxxxxx
      break;

    case 3:
      LedData::Write<0x3C0>(); // 0b001111xxxxxx
      break;

    case 4:
      LedData::Write<0xC00>(); // 0b110000xxxxxx
      break;

    case 5:
      LedData::Write<0xCC0>(); // 0b110011xxxxxx
      break;

    case 6:
      LedData::Write<0xF00>(); // 0b111100xxxxxx
      break;

    case 7:
      LedData::Write<0xFC0>(); // 0b111111xxxxxx
      break;

  }

  for(j = 0; j < 31; j++) {
    for(i = 0; i < 32; i++) {
      if(i == 31) { PinLAT::Set(); }
      PinCLK::Set();
      PinCLK::Clear();
    }
    PinLAT::Clear();
  }

  for(k = 0; k < 32; k++) {
    if(k == 30) { PinLAT::Set(); }
    PinCLK::Set();
    PinCLK::Clear();
  }
  PinLAT::Clear();
}

void leder_3ini::test() {
  LedABC::Write<0>();    // 000xxx
  _delay_ms(1);

  LedABC::Write<0x08>(); // 001xxx
  _delay_ms(1);

  LedABC::Write<0x10>(); // 010xxx
  _delay_ms(1);

  LedABC::Write<0x18>(); // 011xxx
  _delay_ms(1);

  LedABC::Write<0x20>(); // 100xxx
  _delay_ms(1);

  LedABC::Write<0x28>(); // 101xxx
  _delay_ms(1);

  LedABC::Write<0x30>(); // 110xxx
  _delay_ms(1);

  LedABC::Write<0x38>(); // 110xxx
  _delay_ms(1);
}