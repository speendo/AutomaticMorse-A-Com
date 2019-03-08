#include "MorseInterpreter.hpp"
#include "AutomaticMorseACom.hpp"
#include "SignalStorage.hpp"
#include "InputSignal.hpp"
#include <limits.h>
#include <Arduino.h>

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
  // generate a border between dits and dahs in user input
  unsigned int avSignalLength;

  if (ditCount <= 0) {
    avSignalLength = 0;
  }
  else if (ditCount >= PASSWORD_LENGTH) {
    avSignalLength = UINT_MAX;
  }
  else {
    Signals& signals = signalStorage.getSignals(); // can I use a reference here?

    bool used[PASSWORD_LENGTH];
    for (unsigned int i = 0; i < PASSWORD_LENGTH; i++) {
      used[i] = false;
    }

    unsigned int sumDit;
    unsigned int sumDah;

    unsigned int curSignal;
    int curIndex;

    unsigned int dahCount = PASSWORD_LENGTH - ditCount;

    if (ditCount < dahCount) {
      // Count DITs first
      for (unsigned int i = 0; i < ditCount; i++) {
        curSignal = UINT_MAX;
        curIndex = -1;
        for (unsigned int j = 0; j < PASSWORD_LENGTH; j++) {
          // only consider unused signals
          if (!used[j]) {
            if (signals.arr[j] < curSignal) {
              curSignal = signals.arr[j];
              curIndex = j;
            }
          }
        }
        sumDit += curSignal;
        used[curIndex] = true;
      }
      // finally sum up DAHs
      for (unsigned int i = 0; i < PASSWORD_LENGTH; i++) {
        if (!used[i]) {
          sumDah += signals.arr[i];
        }
      }
    } else {
      // Count DAHs first
      for (unsigned int i = 0; i < dahCount; i++) {
        curSignal = 0;
        curIndex = -1;
        for (unsigned int j = 0; j < PASSWORD_LENGTH; j++) {
          // only consider unused signals
          if (!used[j]) {
            if (signals.arr[j] > curSignal) {
              curSignal = signals.arr[j];
              curIndex = j;
            }
          }
        }
        sumDah += curSignal;
        used[curIndex] = true;
      }
      // finally sum up DAHs
      for (unsigned int i = 0; i < PASSWORD_LENGTH; i++) {
        if (!used[i]) {
          sumDit += signals.arr[i];
        }
      }
    }

    // calculate border between dit and dah in user input
    avSignalLength = (sumDit/ditCount + sumDah/(PASSWORD_LENGTH - ditCount)) / 2;
  }
  return avSignalLength;
}
