#ifndef SimplePinInputSignal_hpp
#define SimplePinInputSignal_hpp

#include "InputSignal.hpp"

class SimplePinInputSignal : public InputSignal {
  const int pin;

public:
  SimplePinInputSignal(unsigned int waitMs, unsigned int minEventMs, unsigned int maxSigMs, int attachTo, SignalStorage signalStorage) :
    InputSignal(waitMs, minEventMs, maxSigMs, signalStorage),
    pin(attachTo)
    {
    }

  void setup();

protected:
  bool getSignal();
};

#endif
