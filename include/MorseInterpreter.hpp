#ifndef MorseInterpreter_hpp
#define MorseInterpreter_hpp

#include "AutomaticMorseACom.hpp"
#include "SignalStorage.hpp"
#include "InputSignal.hpp"

class MorseInterpreter {
  const float ditDahThreshold;
  InputSignal& inputSignal;
  SignalStorage& signalStorage;

  bool checkFinished;
  bool passwordCorrect;

public:
  MorseInterpreter(float ditDahThreshold, InputSignal& inputSignal, SignalStorage& signalStorage) :
    ditDahThreshold(ditDahThreshold),
    inputSignal(inputSignal),
    signalStorage(signalStorage)
  {
  }

  void setup();
  void loop();
  void reset();
  bool getCheckFinished();
  bool getPasswordCorrect();

private:
  void comparePW();
  MorsePW getInputPW();
  unsigned int getDitCount();
  unsigned int getAvSignalLength(unsigned int ditCount);
  void quickSort(unsigned int *begin, unsigned int *end);
  void swap(unsigned int *a, unsigned int *b);
};

#endif
