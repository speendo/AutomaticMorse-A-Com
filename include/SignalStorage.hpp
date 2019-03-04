#ifndef SignalStorage_hpp
#define SignalStorage_hpp

#include "AutomaticMorseACom.hpp"

class SignalStorage {
public:
  SignalStorage();
  void reset();
  bool full();
  void push(unsigned int);
  Signals getSignals();

private:
  Signals signals;
  unsigned int current;
};

#endif
