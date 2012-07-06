#include <math.h>
#include <stdlib.h>

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include <timers.h>

#include "ui.h"
#include "modules/list.h"

void *operator new(size_t size)  { return malloc(size); }
void  operator delete(void *ptr) { if (ptr) free(ptr);  }

extern "C" { void __cxa_pure_virtual(void) {} };

UIClass ui;
uint8_t ui_flag, timer_count = 0;

ILed* module;

using namespace Mcucpp::Timers;

inline void null_outputs() {
  typedef PinList<Pa0, Pa1, Pa2, Pa3, Pa4, Pa5, Pa6, Pa7, \
                  Pd0, Pd1, Pd2, Pd3, Pd4, Pd5, Pd6, Pd7> Outputs;

  Outputs::SetConfiguration(Outputs::Out);
  Outputs::Write<0>();
}

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

  module->disable();
  module->shift(ui.get_colors());
}

int main() {
  null_outputs();
  Timer0::EnableInterrupt();

  ui.init();
  module_handle(ui.get_module());
  
  sei();
  
  while(1) {
    if(ui_flag) {
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
    module->disable();
    GICR &= ~(1 << INT2);
    ui_flag = 1;
    ui.interrupt_handler();
    Timer0::Start(Timer0::Div1024);
  }
}

ISR(TIMER0_OVF_vect) {
  ATOMIC {
    if(timer_count == 1) {
      Timer0::Stop();
      timer_count = 0;

      GIFR |=  (1 << INTF2);
      GICR |=  (1 << INT2);
    } else {
      timer_count++;
    }
  }
}