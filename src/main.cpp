#include <Arduino.h>
#include "SignalStorage.hpp"
#include "InputSignal.hpp"
#include "SimplePinInputSignal.hpp"
#include "MorseInterpreter.hpp"
#include "OutputInterface.hpp"
#include "StateController.hpp"

SignalStorage signalStorage = SignalStorage();

SimplePinInputSignal input = SimplePinInputSignal(2000, 100, 3000, 4, signalStorage);

MorseInterpreter morseInterpreter = MorseInterpreter(30, input, signalStorage);

OutputInterface output = OutputInterface(5, 2000, 1000, 0, 0, 0);

StateController controller = StateController(input, output, morseInterpreter);

void setup() {
  controller.setup();
  input.setup();
  morseInterpreter.setup();
  output.setup();
}

void loop() {
  controller.loop();
  input.loop();
  morseInterpreter.loop();
  output.loop();
}
