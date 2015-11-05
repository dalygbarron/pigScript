#include "Script.hh"

#include <vector>


Script::Script(std::vector<Instruction> * pInstructions):
instructions(pInstructions)
{}


Script::~Script()
{
  delete instructions;
}


Instruction const * Script::getInstructionPtr()
{
  return &(*instructions)[0];
}
