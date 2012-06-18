#include <math.h>

#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include <atomic.h>
#include <iopins.h>
#include <pinlist.h>

using namespace Mcucpp::IO;

ISR(INT0_vect);

class UIClass {
friend void INT0_vect();

public:
  void init();
  void handle();

private:
  void interrupt_handler();

  bool flags_changed_p(uint8_t type);
  void toggle_settings_mode();
  void indicate(uint8_t flags);
  void blink();
  void read_settings();
  void write_settings();

  typedef PinList<Pd0, Pd1, Pd3, Pd4> Buttons; // <R, G, B, S>
  typedef PinList<Pd5, Pd6, Pd7> Leds; // <R, G, B>

  uint8_t module, led_flags, flags_store[2][2];

  struct Flags_t {
    uint8_t blink: 1;
    uint8_t settings_mode:  1;
    uint8_t settings_write: 1;
  };

  Flags_t flags;
};