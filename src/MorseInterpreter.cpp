#include <limits.h>
#include "SignalStorage.hpp"

enum MorseStates {
  NULL = -1,
  DIT,
  DAH
};

template < unsigned int PASSWORD_LENGTH >

class MorseInterpreter {
  SignalStorage::Signals signals;

public:
  MorseInterpreter(SignalStorage signalStorage) :
    signals(signalStorage.getSignals())
  {
  }

  bool comparePW(MorseStates correctPW) {

  }

private:
  unsigned int avSignalLength(unsigned int ditCount) {
    unsigned int signalsCp[PASSWORD_LENGTH] = signals; // make a copy
    quickSort(&signalsCp[0], &signalsCp[PASSWORD_LENGTH-1]);

    // generate a border between dits and dahs in user input
    unsigned int avSignalLength;

    if (ditCount <= 0) {
      avSignalLength = 0;
    }
    else if (ditCount >= PASSWORD_LENGTH) {
      avSignalLength = UINT_MAX;
    }
    else {
      // in fact a password should always consist of dits AND dahs, therefore the 2 possibilities above should never be true

      // get average dit length
      unsigned int avDit = 0;
      for (unsigned int i = 0; i < ditCount; i++) {
        avDit = avDit + signalsCp[i];
      }
      avDit = avDit / ditCount;

      // get average dah length
      unsigned int avDah = 0;
      for (unsigned int i = ditCount; i < PASSWORD_LENGTH; i++) {
        avDah = avDah + signalsCp[i];
      }
      avDah = avDah / PASSWORD_LENGTH - ditCount;

      // calculate border between dit and dah in user input
      avSignalLength = (avDit + avDah) / 2;
    }
    return avSignalLength;
  }

  void quicksort(unsigned int *begin, unsigned int *end) {
    unsigned int *ptr;
    unsigned int *split;
    if (end - begin <= 1)
    return;
    ptr = begin;
    split = begin + 1;
    while (++ptr != end) {
      if (*ptr < *begin) {
        swap(ptr, split);
        ++split;
      }
    }
    swap(begin, split - 1);
    quicksort(begin, split - 1);
    quicksort(split, end);
  }

  void swap(unsigned int *a, unsigned int *b) {
    unsigned int tmp = *a;
    *a = *b;
    *b = tmp;
  }

};
