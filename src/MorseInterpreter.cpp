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

    unsigned int lastDit = 0;
    unsigned int lastDah = UINT_MAX;

    unsigned int curDit;
    unsigned int curDah;

    unsigned int sumDit = 0;
    unsigned int sumDah = 0;

    unsigned int value;

    // Iterate ditCount or dahCount times (depends on what is higher)
    for (unsigned int i = 0; i < max(ditCount, (PASSWORD_LENGTH - ditCount)); i++) {
      curDit = UINT_MAX;
      curDah = 0;

      // Iterate over signals
      for (unsigned int j = 0; j < PASSWORD_LENGTH; j++) {
        value = signals.arr[j];

        // Build sum of DITs
        if (i < ditCount) {
          if (value > lastDit && value < curDit) {
            curDit = value;
          }
        } else {
          // don't add anything to sumDit
          curDit = 0;
        }

        // Build sum of DAHs
        if (i < (PASSWORD_LENGTH - ditCount)) {
          if (value < lastDah && value > curDah) {
            curDah = value;
          }
        } else {
          // don't add anything to sumDah
          curDah = 0;
        }
      }
      sumDit += curDit;
      sumDah += curDah;

      lastDit = curDit;
      lastDah = curDah;
    }

    unsigned int avDit = sumDit / ditCount;
    unsigned int avDah = sumDah / (PASSWORD_LENGTH - ditCount);

    // calculate border between dit and dah in user input
    avSignalLength = (avDit + avDah) / 2;
  }
  return avSignalLength;
}
