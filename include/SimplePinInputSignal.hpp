#include "InputSignal.hpp"

class SimplePinInputSignal : InputSignal {
  public:
    SimplePinInputSignal(unsigned int waitMs, unsigned int minEventMs, unsigned int maxSigMs, int attachTo);
    bool getSignal();

  private:
    const int pin;
};
