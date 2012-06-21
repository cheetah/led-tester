#include <math.h>
#include <stdlib.h>

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "ui.h"
#include "modules/list.h"

void *operator new(size_t size)  { return malloc(size); }
void  operator delete(void *ptr) { if (ptr) free(ptr);  }

UIClass ui;
uint8_t ui_flag = 0;

ILed* module;

void module_handle(uint8_t module_type) {
  delete module;
  
  switch(module_type) {
    case p10_1r_e:
      module = new p10_1r;
      break;

    case ld_p16f4_e:
      module = new ld_p16f4;
      break;

    case leder_3ini_e:
      module = new leder_3ini;
      break;

    case leder_xcph16_e:
      module = new leder_xcph16;
      break;

    default:
      module = new p10_1r;
      break;
  }

  module->init();
  module->shift(ui.get_colors());
}

int main() {
  ui.init();
  module_handle(ui.get_module());
  
  sei();
  
  while(1) {
    if(ui_flag) {
      module->disable();

      ui_status status = ui.handle();
      switch(status) {
        case COLOR_CHANGED:
          module->shift(ui.get_colors());
          break;

        case MODULE_CHANGED:
          module_handle(ui.get_module());
          break;

        case CONTINUE:
          _delay_ms(250);
          break;

        case NOTHING:
          ui_flag = 0;
          break;
      }
    } else {
      module->enable();
      module->test();
    }
  }
}

ISR(INT2_vect) {
  ATOMIC {
    ui_flag = 1;
    ui.interrupt_handler();
  }
}