#include "VirtualMachine.hh"

#include "danylib/danylib.hh"

#include "Instruction.hh"


VirtualMachine::VirtualMachine()
{
  for (int i = 0;i < N_VARIABLES;i++)
  {
    variables[i] = 0;
  }
}


VirtualMachine::~VirtualMachine()
{
  for (std::map<char *,addon,danylib_cmpstrptr>::iterator it = functions.begin();
       it != functions.end();++it)
  {
    delete it->first;
  }
}


void VirtualMachine::execute(Script * scriptPtr)
{
  Script script = *scriptPtr;

  int instructionIndex = 0;

  while (instructionIndex != -1 && instructionIndex < script.size())
  {
    Instruction * instruction = script[instructionIndex];

    switch(instruction->code)
    {
    case op_jmp:
      instructionIndex = variables[instruction->args[0]];
      break;

    case op_jeq:
      if (variables[instruction->args[1]] == 0)
        instructionIndex = variables[instruction->args[0]];
      break;

    case op_jne:
      if (variables[instruction->args[1]] != 0)
        instructionIndex = variables[instruction->args[0]];
      break;

    case op_jlt:
      if (variables[instruction->args[1]] < 0)
        instructionIndex = variables[instruction->args[0]];
      break;

    case op_jle:
      if (variables[instruction->args[1]] <= 0)
        instructionIndex = variables[instruction->args[0]];
      break;

    case op_jgt:
      if (variables[instruction->args[1]] > 0)
        instructionIndex = variables[instruction->args[0]];
      break;

    case op_jge:
      if (variables[instruction->args[1]] >= 0)
        instructionIndex = variables[instruction->args[0]];
      break;

    case op_call:
      call(instruction->args);
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
      dump();
      break;

    case op_end:
      instructionIndex = -1;
      break;
    }

    instructionIndex++;
  }

}


void VirtualMachine::registerAddon(addon newAddon,char * name)
{
  functions[name] = newAddon;
}


void VirtualMachine::dump()
{
  for (int i = 0;i < N_VARIABLES;i++)
  {
    printf("variables[%d] = %d\n",i,variables[i]);
  }
}

void VirtualMachine::call(char * args)
{
  if (functions.count(args + 1) == 1)
  {
    //do stuff'
    printf("calling %s\n",args + 1);
  }
  else
  {
    printf("%s is not a registered function, but continuing with execution\n",args + 1);
  }
}
