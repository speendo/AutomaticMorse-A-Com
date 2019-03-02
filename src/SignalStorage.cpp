#include "AutomaticMorseACom.hpp"
class SignalStorage {
  Signals signals;
  unsigned int current;

public:
  SignalStorage() {
    reset();
  }

  void reset() {
    for(unsigned int i = 0; i < PASSWORD_LENGTH; i++) {
      signals.arr[i] = 0;
    }
    current = 0;
  }

  bool full() {
    return current >= PASSWORD_LENGTH;
  }

  void push(unsigned int value) {
    if (!full()) {
      signals.arr[current++] = value;
    }
  }

  Signals getSignals() {
    return signals;
  }
};
