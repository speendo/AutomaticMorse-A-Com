#include <Arduino.h>
#include "InputSignal.hpp"
#include "SimplePinInputSignal.hpp"

InputSignal input = SimplePinInputSignal(1000, 10000, 100000, 4);

void setup() {
}

void loop() {
  // put your main code here, to run repeatedly:
}
