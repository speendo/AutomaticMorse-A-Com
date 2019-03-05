#ifndef StateController_hpp
#define StateController_hpp

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

  void setup();
  void loop();

};

#endif
