#include "InputSignal.hpp"
#include <Arduino.h>
#include "SignalStorage.hpp"

void InputSignal::setup() {
  reset();
}

void InputSignal::loop() {
  if (!error && !finished) { // when in error or finished state, wait for reset
    prevSignal = signal;
    signal = getSmoothSignal();

    if (prevSignal) { // button was pressed ...
      unsigned int currentSignalTime = millis() - validEventMs; // currentSignalTime must be evaluated
      if (signal) { // ... and still is
        if (currentSignalTime > maxSigMs) { // button is pressed too long
          error = true; // go in error state
        }
      } else { // ... and is released
        validEventMs = millis(); // initialise timer
        // signal is valid
        if (signalStorage.full()) {
          error = true; // signalStorage is full - go in error state
        } else {
          signalStorage.push(currentSignalTime); // store signal
        }
      }
    } else { // button was released ...
      if (signal) { // ... and is pressed now
        validEventMs = millis(); // initialise timer
        listening = true;
      } else { // and still isn't pressed
        if (listening) {
          if (millis() - validEventMs > waitMs) {
            if (signalStorage.full()) {
              finished = true; // last command was entered - go in finished state
            } else {
              error = true; // go in error state because signal pause was too long
            }
          }
        }
      }
    }
  }
}

void InputSignal::reset() {
  signal = false;
  prevSignal = signal;
  error = false;
  finished = false;
  listening = false;
  signalStorage.reset();
}

bool InputSignal::getError() {
  return error;
}

bool InputSignal::getFinished() {
  return finished;
}

bool InputSignal::getSmoothSignal() {
  bool curSignal = getSignal();
  unsigned int curMs = millis();

  if (curSignal == prevSignal) { // if signal hasn't changed
    return curSignal;
  } else { // if signal has changed
    bool returnEvent = (curMs - lastEventMs >= minEventMs); // has minEventMs passed?
    lastEventMs = curMs; // anyway, reset lastEventMs if signal has changed
    if (returnEvent) { // minEventMs has passed - return signal change
      return curSignal;
    } else { // minEventMs has not passed - ignore signal change
      return prevSignal;
    }
  }
}
