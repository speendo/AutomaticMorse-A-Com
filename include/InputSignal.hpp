#ifndef InputSignal_hpp
#define InputSignal_hpp

#include "SignalStorage.hpp"

class InputSignal {
  const unsigned int waitMs;
  const unsigned int minEventMs;
  const unsigned int maxSigMs;

  bool signal;
  bool prevSignal;
  bool error;
  bool finished;
  bool listening;

  unsigned long validEventMs;

  unsigned long lastEventMs;

  SignalStorage& signalStorage;

public:
  InputSignal(unsigned int waitMs, unsigned int minEventMs, unsigned int maxSigMs, SignalStorage& signalStorage) :
  waitMs(waitMs),
  minEventMs(minEventMs),
  maxSigMs(maxSigMs),
  signalStorage(signalStorage)
  {
  }

  void setup();
  void loop();
  void reset();
  bool getError();
  bool getFinished();

protected:
  bool getSmoothSignal();
  virtual bool getSignal() = 0; // Abstract method, has to be overridden by derived class

};
#endif
