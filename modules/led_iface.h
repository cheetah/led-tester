#ifndef led_iface
#define led_iface

class ILed {
public:
  virtual void init() = 0;
  virtual void shift(uint8_t state) = 0;
  virtual void test() = 0;
  virtual void enable() = 0;
  virtual void disable() = 0;
};

#endif