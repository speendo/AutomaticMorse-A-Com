#ifndef MorseInterpreter_hpp
#define MorseInterpreter_hpp

#include "SignalStorage.hpp"

enum MorseStates {
  EMPTY = -1,
  DIT,
  DAH
};

template < unsigned int PASSWORD_LENGTH >
class MorseInterpreter {
  struct MorsePW{
    MorseStates arr[];
  };

  SignalStorage::Signals signals;
  float ditDahThreshold;

public:
  MorseInterpreter(SignalStorage signalStorage, float ditDahThreshold);
  bool comparePW(MorsePW correctPW);

private:
  MorsePW getInputPW(MorsePW correctPW);
  unsigned int getDitCount(MorsePW correctPW);
  unsigned int getAvSignalLength(unsigned int ditCount);
  void quickSort(unsigned int *begin, unsigned int *end);
  void swap(unsigned int *a, unsigned int *b);
};

#endif
