#ifndef MorseInterpreter_hpp
#define MorseInterpreter_hpp

#include "AutomaticMorseACom.hpp"
#include "SignalStorage.hpp"
#include "InputSignal.hpp"

class MorseInterpreter {

public:
  MorseInterpreter(float ditDahThreshold, InputSignal& inputSignal, SignalStorage& signalStorage);
  void setup();
  void loop();
  void reset();
  bool getPasswordCorrect();
  bool getCheckFinished();

private:
  const float ditDahThreshold;
  InputSignal& inputSignal;
  SignalStorage& signalStorage;

  bool passwordCorrect;
  bool checkFinished;

  void comparePW();
  MorsePW getInputPW();
  unsigned int getDitCount();
  unsigned int getAvSignalLength(unsigned int ditCount);
  void quickSort(unsigned int *begin, unsigned int *end);
  void swap(unsigned int *a, unsigned int *b);
};

#endif
