#include "InputSignal.hpp"
#include "SimplePinInputSignal.hpp"
#include "OutputInterface.hpp"

class MorseInterpreter {
  const InputSignal input;
  const OutputInterface output;

public:
  MorseInterpreter(InputSignal input, OutputInterface output) :
    input(input),
    output(output)
    {
    }
};
