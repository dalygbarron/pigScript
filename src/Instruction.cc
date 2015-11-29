#include "Instruction.hh"

#include <stdint.h>
#include <stdio.h>


#define OP_CODE_SIZE 1
#define LABEL_SIZE 4
#define VAR_SIZE 1
#define CONST_SIZE 4



Instruction::Instruction(OpCode pCode):
code(pCode)
{
  args = nullptr;
}


Instruction::Instruction(OpCode pCode,uint8_t * pArgs):
code(pCode),
args(pArgs)
{}


Instruction::Instruction(FILE * inFile)
{
  code = op_jmp;
  fread(&code,OP_CODE_SIZE,1,inFile);

  switch(code)
  {
  case op_jmp:
    args = new uint8_t[LABEL_SIZE];
    fread(args,LABEL_SIZE,1,inFile);
    break;

  case op_jeq:
  case op_jne:
  case op_jlt:
  case op_jle:
  case op_jgt:
  case op_jge:
    args = new uint8_t[LABEL_SIZE + VAR_SIZE];
    fread(args,LABEL_SIZE,1,inFile);
    fread(args + LABEL_SIZE,VAR_SIZE,1,inFile);
    break;

  case op_set:
  case op_move:
    args = new uint8_t[CONST_SIZE + VAR_SIZE];
    fread(args,CONST_SIZE + VAR_SIZE,2,inFile);
    break;

  case op_add:
  case op_sub:
    args = new uint8_t[3];
    fread(args,1,3,inFile);
    break;

  case op_call:
    int argLength;
    fread(&argLength,2,1,inFile);
    args = new uint8_t[argLength];
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
