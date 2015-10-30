#include "Instruction.hh"

Instruction::Instruction(OpCode pCode,uint32_t * pArgs,int pNArgs):
code(pCode),
args(pArgs),
nArgs(pNargs)
{}


Instruction::~Instruction()
{
  delete[] args;
}
