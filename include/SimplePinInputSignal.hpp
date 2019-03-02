#ifndef SimplePinInputSignal_hpp
#define SimplePinInputSignal_hpp

#include "InputSignal.hpp"

class SimplePinInputSignal : public InputSignal {
  public:
    SimplePinInputSignal(unsigned int waitMs, unsigned int minEventMs, unsigned int maxSigMs, int attachTo);
    bool getSignal();

  private:
    const int pin;
};

#endif
