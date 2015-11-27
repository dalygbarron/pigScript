#include "Instruction.hh"

#include <stdint.h>
#include <stdio.h>


#define OP_CODE_SIZE 1


Instruction::Instruction(OpCode pCode):
code(pCode)
{
  args = nullptr;
}


Instruction::Instruction(OpCode pCode,char * pArgs):
code(pCode),
args(pArgs)
{}


Instruction::Instruction(FILE * inFile)
{
  code = op_jmp;
  fread(&code,OP_CODE_SIZE,1,inFile);

  switch(code)
  {
  case op_jeq:
  case op_jne:
  case op_jlt:
  case op_jle:
  case op_jgt:
  case op_jge:
    args = new char;
    fread(args,1,1,inFile);
    break;

  case op_set:
  case op_move:
    args = new char[2];
    fread(args,1,2,inFile);
    break;

  case op_add:
  case op_sub:
    args = new char[3];
    fread(args,1,3,inFile);
    break;

  case op_call:
    int argLength;
    fread(&argLength,2,1,inFile);
    args = new char[argLength];
    args[0] = argLength & 0xFF;
    args[1] = (argLength >> 8) & 0xFF;
    fread(args + 2,1,argLength - 2,inFile);
    break;
  }
}


Instruction::~Instruction()
{
  if (args != nullptr)
  {
    delete[] args;
    args = nullptr;
  }
}


void Instruction::toFile(FILE * outFile)
{
  fwrite(&code,OP_CODE_SIZE,1,outFile);

  switch(code)
  {
  case op_jeq:
  case op_jne:
  case op_jlt:
  case op_jle:
  case op_jgt:
  case op_jge:
    fwrite(args,1,1,outFile);
    break;

  case op_set:
  case op_move:
    fwrite(args,1,2,outFile);
    break;

  case op_add:
  case op_sub:
    fwrite(args,1,3,outFile);
    break;

  case op_call:
    int argLength = args[0] | (args[1] << 8);
    fwrite(args,1,argLength,outFile);
    break;
  }
}
