#include "SimplePinInputSignal.hpp"
#include "InputSignal.hpp"
#include <Arduino.h>

void SimplePinInputSignal::setup() {
  pinMode(pin, INPUT);
  InputSignal::setup();
}

bool SimplePinInputSignal::getSignal() {
  return digitalRead(pin);
}
