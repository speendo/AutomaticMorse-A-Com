template < unsigned int PASSWORD_LENGTH >

class SignalStorage {
  unsigned int signals[PASSWORD_LENGTH];
  unsigned int current;

public:
  SignalStorage() {
    reset();
  }

  void reset() {
    memset(signals, 0, sizeof(signals)); // reset array
    current = 0;
  }

  bool full() {
    return current >= PASSWORD_LENGTH;
  }

  void push(unsigned int value) {
    if (!full()) {
      signals[current++] = value;
    }
  }
};
