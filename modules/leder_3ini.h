#include <math.h>

#include <avr/io.h>
#include <util/delay.h>

#include <iopins.h>
#include <timers.h>
#include <pinlist.h>

#include "led_iface.h"

using namespace Mcucpp::IO;
using namespace Mcucpp::Timers;

class leder_3ini: public ILed {
public:
  leder_3ini();
  ~leder_3ini();
  
  void shift(uint8_t state);
  void test();
  void enable();
  void disable();

private:
  
  typedef PinList<Pd5, Pd6, Pd7, Pd1, Pd0, Pd3, \
                  Pa6, Pa2, Pa7, Pa3, Pa4, Pa0> Led;

  typedef Pd4 PWM; // OCR1B

  typedef Led::Slice<3, 3> LedABC;
  typedef Led::Slice<6, 6> LedData;

  typedef Led::Pin<0>  PinCON;
  typedef Led::Pin<1>  PinCLK;
  typedef Led::Pin<2>  PinLAT;
  typedef Led::Pin<3>  PinA;
  typedef Led::Pin<4>  PinB;
  typedef Led::Pin<5>  PinC;

  typedef Led::Pin<6>  PinR1;
  typedef Led::Pin<7>  PinR2;
  typedef Led::Pin<8>  PinG1;
  typedef Led::Pin<9>  PinG2;
  typedef Led::Pin<10> PinB1;
  typedef Led::Pin<11> PinB2;

};