#include "ui.h"

uint8_t ee_module EEMEM = 0;

void UIClass::init() {
  Buttons::SetConfiguration(Buttons::In);
  Leds::SetConfiguration(Leds::Out);

  MCUCSR |= (0 << ISC2); // INT2, by falling front
  GICR   |= (1 << INT2); // INT2 enable

  read_settings();

  ATOMIC {
    indicate(module);
    _delay_ms(3000);
    indicate(0);
  }
}

ui_status UIClass::handle() {
  if(flags.settings_mode) {
    if(flags_changed_p(1)) { }
    blink();

    return CONTINUE;
  } else {
    if(flags_changed_p(0)) {
      indicate(led_flags);

      return COLOR_CHANGED;
    }
  }

  if(flags.settings_write) {
    write_settings();

    return MODULE_CHANGED;
  }

  return NOTHING;
}

uint8_t UIClass::get_module() {
  return module;
}

uint8_t UIClass::get_colors() {
  return flags_store[0][0];
}

void UIClass::toggle_settings_mode() {
  if(flags.settings_mode) {
    module = led_flags;
    if(flags_store[1][1] != module) { flags.settings_write = 1; }
    flags_store[1][1] = led_flags;

    led_flags = flags_store[0][1];
    indicate(led_flags);
    
    flags.settings_mode = 0;
  } else {
    flags_store[0][1] = led_flags;
    
    led_flags = module;
    
    flags.settings_mode = 1;
  }
}
 
bool UIClass::flags_changed_p(uint8_t type) {
  if(led_flags != flags_store[type][0]) {
    flags_store[type][0] = led_flags;
    return true;
  } else {
    return false;
  }
}

void UIClass::indicate(uint8_t flags) {
  Leds::Write<0>();
  Leds::Set(flags);
}

void UIClass::blink() {
  if(flags.blink) {
    indicate(0);
    flags.blink = 0;
  } else {
    indicate(led_flags);
    flags.blink = 1;
  }
}

void UIClass::read_settings() {
  module = eeprom_read_byte(&ee_module);
  if(module > 7) module &= 0b00000111;
  flags_store[1][1] = module;
}

void UIClass::write_settings() {
  eeprom_write_byte(&ee_module, module);
  flags.settings_write = 0;
}

uint8_t UIClass::read_buttons() {
  uint8_t state = Buttons::PinRead();

  while(state == 0b1111) {
    state = Buttons::PinRead();
  }

  return state;
}

void UIClass::interrupt_handler() {
  switch(read_buttons()) {
    case RED:
      led_flags ^= (1 << 0);
      break;

    case GREEN:
      led_flags ^= (1 << 1);
      break;

    case BLUE:
      led_flags ^= (1 << 2);
      break;

    case SETTINGS:
      toggle_settings_mode();
      break;

    default:
      break;
  }
}