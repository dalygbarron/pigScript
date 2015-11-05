#include "Instruction.hh"

#include <stdint.h>


Instruction::Instruction(OpCode pCode,uint32_t * pArgs,int pNArgs):
code(pCode),
args(pArgs),
nArgs(pNArgs)
{}


Instruction::~Instruction()
{
  delete[] args;
}
