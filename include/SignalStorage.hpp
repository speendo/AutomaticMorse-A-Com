#ifndef SignalStorage_hpp
#define SignalStorage_hpp

#include "AutomaticMorseACom.hpp"

class SignalStorage {
  Signals signals;
  unsigned int current;

public:
  SignalStorage();

  void reset();
  bool full();
  void push(unsigned int value);
  Signals getSignals();

};

#endif
