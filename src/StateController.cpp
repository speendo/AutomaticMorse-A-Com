#include "InputSignal.hpp"
#include "OutputInterface.hpp"
#include "MorseInterpreter.hpp"

class StateController {

  InputSignal& input;
  OutputInterface& output;
  MorseInterpreter& morseInterpreter;

public:
  StateController(InputSignal& input, OutputInterface& output, MorseInterpreter& morseInterpreter) :
    input(input),
    output(output),
    morseInterpreter(morseInterpreter)
  {
  }

  void setup() {

  }

  void loop() {
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
};
