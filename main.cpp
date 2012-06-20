#include <math.h>

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "ui.h"
#include "modules/p10_1r.h"
#include "modules/leder_3ini.h"

UIClass ui;

int main() {
  ui.init();
  sei();
  while(1) {
    ui.handle();
    _delay_ms(250);
  }
}

ISR(INT2_vect) {
  ui.interrupt_handler();
}

/*leder_3ini module;

int main() {
  module.init();
  while(1) {
    module.shift(7);
    module.test();
  }
}*/