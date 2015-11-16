#include "Script.hh"

#include <vector>


Script::~Script()
{
  //TODO: delete the instructions
}


Instruction * * Script::getInstructionPtr()
{
  return &(instructions[0]);
}
