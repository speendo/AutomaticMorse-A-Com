#include "MorseInterpreter.hpp"
#include "AutomaticMorseACom.hpp"
#include "SignalStorage.hpp"
#include "InputSignal.hpp"
#include <limits.h>

void MorseInterpreter::setup() {
  reset();
}

void MorseInterpreter::loop() {
  if (inputSignal.getFinished()) {
    comparePW();
    checkFinished = true;
  }
}

void MorseInterpreter::reset() {
  passwordCorrect = false;
  checkFinished = false;
}

bool MorseInterpreter::getCheckFinished() {
  return checkFinished;
}

bool MorseInterpreter::getPasswordCorrect() { // once this is called, passwordCorrect is reset to false
  bool returnPasswordCorrect = passwordCorrect;
  reset();
  return returnPasswordCorrect;
}

void MorseInterpreter::comparePW() {
  MorsePW inputPW = getInputPW();

  bool tempPasswordCorrect = true;

  for (unsigned int i=0; i < PASSWORD_LENGTH; i++) {
    if (inputPW.arr[i] != PASSWORD[i]) {
      tempPasswordCorrect = false;
    }
  }

  passwordCorrect = tempPasswordCorrect;
}

MorsePW MorseInterpreter::getInputPW() {
  Signals signals = signalStorage.getSignals();
  unsigned int ditCount = getDitCount();
  unsigned int avSignalLength = getAvSignalLength(ditCount);

  MorsePW returnPW = MorsePW{};
  for (unsigned int i = 0; i < PASSWORD_LENGTH; i++) {
    if (signals.arr[i] < (avSignalLength - (ditDahThreshold * avSignalLength))) {
      returnPW.arr[i] = DIT;
    } else if (signals.arr[i] > (avSignalLength + (ditDahThreshold * avSignalLength))) {
      returnPW.arr[i] = DAH;
    } else {
      returnPW.arr[i] = EMPTY;
    }
  }

  return returnPW;
}

unsigned int MorseInterpreter::getDitCount() {
  unsigned int ditCount = 0;
  for (unsigned int i = 0; i < PASSWORD_LENGTH; i++) {
    if (PASSWORD[i] == DIT) {
      ditCount++;
    }
  }
  return ditCount;
}

unsigned int MorseInterpreter::getAvSignalLength(unsigned int ditCount) {
  // make a copy
  Signals signalsCp = signalStorage.getSignals();

  quickSort(&signalsCp.arr[0], &signalsCp.arr[PASSWORD_LENGTH-1]);

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
      avDit = avDit + signalsCp.arr[i];
    }
    avDit = avDit / ditCount;

    // get average dah length
    unsigned int avDah = 0;
    for (unsigned int i = ditCount; i < PASSWORD_LENGTH; i++) {
      avDah = avDah + signalsCp.arr[i];
    }
    avDah = avDah / PASSWORD_LENGTH - ditCount;

    // calculate border between dit and dah in user input
    avSignalLength = (avDit + avDah) / 2;
  }
  return avSignalLength;
}

void MorseInterpreter::quickSort(unsigned int *begin, unsigned int *end) {
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

void MorseInterpreter::swap(unsigned int *a, unsigned int *b) {
  unsigned int tmp = *a;
  *a = *b;
  *b = tmp;
}
