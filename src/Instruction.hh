//a single instruction that gets executed yee


#ifndef INSTRUCTION_H
#define INSTRUCTION_H


#include <stdint.h>
#include <stdio.h>


//the types of instructions there are
enum OpCode
{
  op_jmp,
  op_jeq,
  op_jne,
  op_jlt,
  op_jle,
  op_jgt,
  op_jge,
  op_call,
  op_set,
  op_add,
  op_sub,
  op_move,
  op_dump,
  op_end
};


class Instruction
{
public:
  //create an instruction without any arguments
  Instruction(OpCode pCode);

  //creates an instruction with it's op code, it's arguments and the number of them
  //it takes ownership of those args too
  Instruction(OpCode pCode,char * pArgs);

  //creates an instruction from a file
  Instruction(FILE * inFile);

  //deletes the instruction and it's data
  ~Instruction();

  //save the instruction to an open file
  void toFile(FILE * outFile);

  //instruction's opcode
  OpCode code;
  //instruction's arguments
  char * args;
};


#endif
