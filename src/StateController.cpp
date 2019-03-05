#include "StateController.hpp"
#include "InputSignal.hpp"
#include "OutputInterface.hpp"
#include "MorseInterpreter.hpp"

void StateController::setup() {

}

void StateController::loop() {
  if (!output.actionsBlocked()) {
    if (input.getError()) {
      output.setDeny();
      input.reset();
    } else if (morseInterpreter.getCheckFinished()) {
      if (morseInterpreter.getPasswordCorrect()) {
        output.setGrant();
        input.reset();
      } else {
        output.setDeny();
        input.reset();
      }
    }
  }
}
