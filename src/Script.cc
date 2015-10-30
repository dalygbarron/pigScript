#include "Script.hh"

#include <vector>


Script::Script(std::vector<Instruction> pInstructions):
instructions(pInstructions)
{}


Script::~Script()
{
  for (std::vector<Instruction>::iterator it = instructions.begin();
       it != instructions.end(); ++it)
  {
    delete *it;
  }
}


Instruction const * Script::getInstructionPtr()
{
  return &instructions[0];
}
