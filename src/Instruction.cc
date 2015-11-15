#include "Instruction.hh"

#include <stdint.h>


Instruction::Instruction(OpCode pCode):
code(pCode)
{
  args = nullptr;
}


Instruction::Instruction(OpCode pCode,char * pArgs):
code(pCode),
args(pArgs)
{}


Instruction::~Instruction()
{
  if (args != nullptr)
  {
    delete[] args;
    args = nullptr;
  }
}
