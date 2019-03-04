#include "InputSignal.hpp"
#include <Arduino.h>

class SimplePinInputSignal : public InputSignal {
  const int pin;

public:
  SimplePinInputSignal(unsigned int waitMs, unsigned int minEventMs, unsigned int maxSigMs, int attachTo, SignalStorage signalStorage) :
    InputSignal(waitMs, minEventMs, maxSigMs, signalStorage),
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
