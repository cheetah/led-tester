#include "leder_3ini.h"

void leder_3ini::init() {
  Led::SetConfiguration(Led::Out);

  DDRB |= (1 << 1);

  TCCR1A |= ((0 << COM1A1) | (1 << COM1A0) | (0 << WGM11) | (0 << WGM10));
  TCCR1B |= ((0 << WGM13)  | (1 << WGM12)  | (0 << CS12)  | (0 << CS11) | (1 << CS10));
                
  OCR1AH = 0;
  OCR1AL = 0;

  enable();
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
      PinR1::Clear(); PinR2::Clear();
      PinG1::Clear(); PinG2::Clear();
      PinB1::Clear(); PinB2::Clear();
      break;

    case 1:
      PinR1::Set(); PinR2::Set();
      PinG1::Clear(); PinG2::Clear();
      PinB1::Clear(); PinB2::Clear();      
      break;

    case 2:
      PinR1::Clear(); PinR2::Clear();
      PinG1::Set(); PinG2::Set();
      PinB1::Clear(); PinB2::Clear();
      break;

    case 3:
      PinR1::Set(); PinR2::Set();
      PinG1::Set(); PinG2::Set();
      PinB1::Clear(); PinB2::Clear();
      break;

    case 4:
      PinR1::Clear(); PinR2::Clear();
      PinG1::Clear(); PinG2::Clear();
      PinB1::Set(); PinB2::Set();
      break;

    case 5:
      PinR1::Set(); PinR2::Set();
      PinG1::Clear(); PinG2::Clear();
      PinB1::Set(); PinB2::Set();
      break;

    case 6:
      PinR1::Clear(); PinR2::Clear();
      PinG1::Set(); PinG2::Set();
      PinB1::Set(); PinB2::Set();
      break;

    case 7:
      PinR1::Set(); PinR2::Set();
      PinG1::Set(); PinG2::Set();
      PinB1::Set(); PinB2::Set();
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
  PinA::Clear();
  PinB::Clear();
  PinC::Clear();
  _delay_ms(1);

  PinA::Set();
  _delay_ms(1);

  PinA::Clear();
  PinB::Set();
  _delay_ms(1);

  PinA::Set();
  _delay_ms(1);

  PinA::Clear();
  PinB::Clear();
  PinC::Set();
  _delay_ms(1);

  PinA::Set();
  _delay_ms(1);

  PinA::Clear();
  PinB::Set();
  _delay_ms(1);

  PinA::Set();
  _delay_ms(1);
}