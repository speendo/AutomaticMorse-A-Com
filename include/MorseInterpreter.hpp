#ifndef MorseInterpreter_hpp
#define MorseInterpreter_hpp

#include "AutomaticMorseACom.hpp"
#include "SignalStorage.hpp"

class MorseInterpreter {

public:
  MorseInterpreter(SignalStorage signalStorage, float ditDahThreshold);
  bool comparePW(MorsePW correctPW);

private:
  Signals signals;
  float ditDahThreshold;

  MorsePW getInputPW(MorsePW correctPW);
  unsigned int getDitCount(MorsePW correctPW);
  unsigned int getAvSignalLength(unsigned int ditCount);
  void quickSort(unsigned int *begin, unsigned int *end);
  void swap(unsigned int *a, unsigned int *b);
};

#endif
