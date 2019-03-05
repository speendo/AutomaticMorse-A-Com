#include "SignalStorage.hpp"
#include "AutomaticMorseACom.hpp"

SignalStorage::SignalStorage() {
  reset();
}

void SignalStorage::reset() {
  for(unsigned int i = 0; i < PASSWORD_LENGTH; i++) {
    signals.arr[i] = 0;
  }
  current = 0;
}

bool SignalStorage::full() {
  return current >= PASSWORD_LENGTH;
}

void SignalStorage::push(unsigned int value) {
  if (!full()) {
    signals.arr[current++] = value;
  }
}

Signals& SignalStorage::getSignals() {
  return signals;
}
