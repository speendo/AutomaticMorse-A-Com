#include "InputSignal.hpp"
#include <Arduino.h>

class SimplePinInputSignal : InputSignal {
  const int pin;

public:
  SimplePinInputSignal(unsigned int waitMs, unsigned int minEventMs, unsigned int maxSigMs, int attachTo) :
    InputSignal(waitMs, minEventMs, maxSigMs),
    pin(attachTo)
    {
    }

  void setup() {
    pinMode(pin, INPUT);
    InputSignal::setup();
  }

protected:
  bool getSignal() {
    return digitalRead(pin);
  }
};
