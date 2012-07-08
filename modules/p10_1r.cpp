#include "p10_1r.h"

p10_1r::p10_1r() {
  Led::SetConfiguration(Led::Out);
}

p10_1r::~p10_1r() {
  Led::Write<0>();
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

  _delay_ms(5);

  for(i = 0; i < 128; i++) {
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