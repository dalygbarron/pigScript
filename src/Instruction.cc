#include "Instruction.hh"

#include <stdint.h>


Instruction::Instruction(OpCode pCode,uint32_t * pArgs,int pNArgs):
code(pCode),
args(pArgs),
strings(pStrings)
nStrings(pNStrings)
{}


Instruction::~Instruction()
{
  delete[] args;
  for (int i = 0;i < nStrings;i++)
  {
    delete[] strings[i];
  }
}
