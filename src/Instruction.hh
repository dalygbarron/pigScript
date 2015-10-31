//a single instruction that gets executed yee


#ifndef INSTRUCTION_H
#define INSTRUCTION_H


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
  Instruction(OpCode pCode,uint32_t * pArgs,int pNArgs);

  //deletes the instruction and it's data
  ~Instruction();

  //instruction's opcode
  OpCode const code;
  //instruction's arguments
  uint32_t const * args;
  //number of arguments
  int const nArgs;
};


#endif
