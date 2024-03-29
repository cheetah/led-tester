#include <math.h>
#include <stdio.h>

#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include <atomic.h>
#include <iopins.h>
#include <pinlist.h>

using namespace Mcucpp::IO;

ISR(INT2_vect);

enum ui_status {
  COLOR_CHANGED,
  MODULE_CHANGED,
  CONTINUE,
  NOTHING,
};

class UIClass {
friend void INT2_vect();

public:
  void init();
  ui_status handle();

  uint8_t get_module();
  uint8_t get_colors();

private:
  void interrupt_handler();

  bool flags_changed_p(uint8_t type);
  void toggle_settings_mode();
  void indicate(uint8_t flags);
  void blink();
  void read_settings();
  void write_settings();

  uint8_t read_buttons();

  typedef PinList<Pb0, Pb1, Pb3, Pb4> Buttons; // <R, G, B, S>
  typedef PinList<Pb5, Pb6, Pb7> Leds; // <R, G, B>

  enum buttons_e {
    RED      = 0b1110,
    GREEN    = 0b1101,
    BLUE     = 0b1011,
    SETTINGS = 0b0111,
  };

  uint8_t module, led_flags, flags_store[2][2];

  struct Flags_t {
    uint8_t blink: 1;
    uint8_t settings_mode:  1;
    uint8_t settings_write: 1;
  };

  Flags_t flags;
};