#include "led_iface.h"

#include "leder_xcph16.h"
#include "leder_3ini.h"
#include "ld_p16f4.h"
#include "p10_1r.h"

enum modules_list {
  p10_1r_e       = 0b001,
  ld_p16f4_e     = 0b010,
  leder_3ini_e   = 0b011,
  leder_xcph16_e = 0b100,
};