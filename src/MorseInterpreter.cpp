//#include "MorseInterpreter.hpp"
#include <limits.h>
#include "SignalStorage.hpp"

enum MorseStates {
  EMPTY = -1,
  DIT,
  DAH
};

template < unsigned int PASSWORD_LENGTH >
class MorseInterpreter {
  SignalStorage::Signals signals;
  float ditDahThreshold;

  struct MorsePW {
    MorseStates arr[PASSWORD_LENGTH];
  };

public:
  MorseInterpreter(SignalStorage signalStorage, float ditDahThreshold) :
    signals(signalStorage.getSignals()),
    ditDahThreshold(ditDahThreshold)
  {
  }

  bool comparePW(MorsePW correctPW) {
    MorsePW inputPW[] = getInputPW(correctPW);

    bool passwordCorrect = true;

    for (unsigned int i=0; i < PASSWORD_LENGTH; i++) {
      if (inputPW != correctPW) {
        passwordCorrect = false;
      }
    }

    return passwordCorrect;
  }

private:
  MorsePW getInputPW(MorsePW correctPW) {
    unsigned int ditCount = getDitCount(correctPW);
    unsigned int avSignalLength = getAvSignalLength(ditCount);

    MorsePW returnPW = MorsePW{};
    for (unsigned int i = 0; i < PASSWORD_LENGTH; i++) {
      if (signals.arr[i] < (avSignalLength - (ditDahThreshold * avSignalLength))) {
        returnPW[i] = DIT;
      } else if (signals.arr[i] > (avSignalLength + (ditDahThreshold * avSignalLength))) {
        returnPW[i] = DAH;
      } else {
        returnPW[i] = EMPTY;
      }
    }

    return returnPW;
  }

  unsigned int getDitCount(MorsePW correctPW) {
    unsigned int ditCount = 0;
    for (unsigned int i = 0; i < PASSWORD_LENGTH; i++) {
      if (correctPW.arr[i] == DIT) {
        ditCount++;
      }
    }
    return ditCount;
  }

  unsigned int getAvSignalLength(unsigned int ditCount) {
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

  void quickSort(unsigned int *begin, unsigned int *end) {
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
    quickSort(begin, split - 1);
    quickSort(split, end);
  }

  void swap(unsigned int *a, unsigned int *b) {
    unsigned int tmp = *a;
    *a = *b;
    *b = tmp;
  }

};
