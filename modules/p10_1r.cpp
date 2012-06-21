#include "p10_1r.h"

void p10_1r::init() {
  Led::SetConfiguration(Led::Out);
}

void p10_1r::enable() {
  PinOE::Set();
}

void p10_1r::disable() {
  PinOE::Clear();
}

void p10_1r::shift(uint8_t state) {
  uint8_t i;
  
  switch(state) {
    case 0:
      PinDATA::Set();
      break;

    default:
      PinDATA::Clear();
      break;
  }

  for(i = 0; i < 32; i++) {
    PinCLK::Set();
    PinCLK::Clear();
  }

  PinLAT::Set();
  PinLAT::Clear();
}

void p10_1r::test() {
  PinA::Clear();
  PinB::Clear();
  _delay_ms(1);

  PinA::Set();
  _delay_ms(1);

  PinA::Clear();
  PinB::Set();
  _delay_ms(1);

  PinA::Set();
  _delay_ms(1);
}