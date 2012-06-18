#include <math.h>

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "ui.h"

UIClass ui;

int main() {
  ui.init();
  sei();
  while(1) {
    ui.handle();
    _delay_ms(250);
  }
}

ISR(INT0_vect) {
  ui.interrupt_handler();
}