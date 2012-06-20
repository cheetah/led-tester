#include <math.h>

#include <avr/io.h>
#include <util/delay.h>

#include <iopins.h>
#include <pinlist.h>

#include "led_iface.h"

using namespace Mcucpp::IO;

class p10_1r: public ILed {
public:
  void init();
  void shift(uint8_t state);
  void test();
  void enable();
  void disable();

private:
  
  typedef PinList<Pc0, Pc1, Pc2, Pc3, Pc4, Pc5> Led;

  typedef Led::Pin<0> PinOE;
  typedef Led::Pin<1> PinCLK;
  typedef Led::Pin<2> PinLAT;
  typedef Led::Pin<3> PinA;
  typedef Led::Pin<4> PinB;
  typedef Led::Pin<5> PinDATA;
};