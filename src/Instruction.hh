//a single instruction that gets executed yee


#ifndef INSTRUCTION_H
#define INSTRUCTION_H


#include <stdint.h>


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
  //creates an instruction with it's op code, it's arguments and the number of them
  //it takes ownership of those args too
  Instruction(OpCode pCode,int * pArgs,char * * pStrings,int pNStrings);

  //deletes the instruction and it's data
  ~Instruction();

  //instruction's opcode
  OpCode const code;
  //instruction's arguments
  int * args;
  //instruction's string literals
  char * * strings;
  //the number of strings
  int nStrings;
};


#endif
