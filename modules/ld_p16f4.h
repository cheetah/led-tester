#include <math.h>

#include <avr/io.h>
#include <util/delay.h>

#include <iopins.h>
#include <timers.h>
#include <pinlist.h>

#include "led_iface.h"

using namespace Mcucpp::IO;

class ld_p16f4: public ILed {
public:
  ld_p16f4();
  ~ld_p16f4();

  void shift(uint8_t state);
  void test();
  void enable();
  void disable();

private:
  
  typedef PinList<Pd5, Pd6, Pd7, Pa6, Pa2, Pa7, Pa3, Pa4, Pa0> Led;

  typedef Led::Slice<3, 6> LedData;

  typedef Led::Pin<0>  PinOE;
  typedef Led::Pin<1>  PinCLK;
  typedef Led::Pin<2>  PinLAT;

  typedef Led::Pin<3>  PinR1;
  typedef Led::Pin<4>  PinR2;
  typedef Led::Pin<5>  PinG1;
  typedef Led::Pin<6>  PinG2;
  typedef Led::Pin<7>  PinB1;
  typedef Led::Pin<8>  PinB2;

};