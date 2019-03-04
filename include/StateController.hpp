#include "InputSignal.hpp"
#include "OutputInterface.hpp"
#include "MorseInterpreter.hpp"

class StateController {
public:
  StateController(InputSignal& input, OutputInterface& output, MorseInterpreter& morseInterpreter);
  void setup();
  void loop();

private:
  InputSignal& input;
  OutputInterface& output;
  MorseInterpreter& morseInterpreter;
};
