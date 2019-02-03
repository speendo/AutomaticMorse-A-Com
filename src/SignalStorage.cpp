#include <limits.h>

template < unsigned int PASSWORD_LENGTH >

class SignalStorage {
  struct Signals {
    unsigned int arr[PASSWORD_LENGTH];
  } signals;
  unsigned int current;

public:
  SignalStorage() {
    reset();
  }

  void reset() {
    memset(signals.arr, 0, sizeof(signals.arr)); // reset array
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
