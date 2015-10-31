#include "VirtualMachine.hh"

#include "Instruction.hh"


void VirtualMachine::execute(Script script)
{
  instruction = script.getInstructionPtr();
  while (instruction != NULL)
  {
    switch(instruction->code)
    {
    case op_jmp:
      instruction = script.getInstructionPtr() + variables[instruction->args[0]];
      break;

    case op_jeq:
      if (variables[instruction->args[1]] == 0)
        instruction = script.getInstructionPtr() + variables[instruction->args[0]];
      break;

    case op_jne:
      if (variables[instruction->args[1]] != 0)
        instruction = script.getInstructionPtr() + variables[instruction->args[0]];
      break;

    case op_jlt:
      if (variables[instruction->args[1]] < 0)
        instruction = script.getInstructionPtr() + variables[instruction->args[0]];
      break;

    case op_jle:
      if (variables[instruction->args[1]] <= 0)
        instruction = script.getInstructionPtr() + variables[instruction->args[0]];
      break;

    case op_jgt:
      if (variables[instruction->args[1]] > 0)
        instruction = script.getInstructionPtr() + variables[instruction->args[0]];
      break;

    case op_jge:
      if (variables[instruction->args[1]] >= 0)
        instruction = script.getInstructionPtr() + variables[instruction->args[0]];
      break;

    case op_call:
      if (functions.count(instruction->args[1]) == 1)
      {
        //do stuff
      }
      else
      {
        printf("%s is not a registered function, but continuing with execution\n",
               instruction->args[1]);
      }
      break;

    case op_set:
      variables[instruction->args[1]] = instruction->args[0];
      break;

    case op_add:
      variables[instruction->args[2]] = variables[instruction->args[0]] +
                                        variables[instruction->args[1]];
      break;

    case op_sub:
      variables[instruction->args[2]] = variables[instruction->args[0]] -
                                        variables[instruction->args[1]];
      break;

    case op_move:
      variables[instruction->args[1]] = variables[instruction->args[0]];
      break;

    case op_dump:
      int i = 0;
      for (std::vector<int>::iterator it = variables.begin();it != variables.end(); ++it)
      {
        printf("variables[%d] = %d\n",i,*it);
        i++;
      }
      break;

    case op_end:
      instruction = NULL;
      break;
    }
  }

}


void VirtualMachine::register(int (func*)(void * args,int nArgs),char const * name)
{

}
