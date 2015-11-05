//basically just a collection of instructions to be executed


#ifndef SCRIPT_H
#define SCRIPT_H


#include <vector>

#include "Instruction.hh"


class Script
{
public:
  //create a new script and give it it's instructions
  Script(std::vector<Instruction> * pInstructions);

  //destroy the script and it's instructions
  ~Script();

  //gives you a pointer to the first instruction
  Instruction const * getInstructionPtr();

private:
  //the instructions that it is made up of
  std::vector<Instruction> * instructions;
};


#endif
