#include "VirtualMachine.hh"

#include "Instruction.hh"


VirtualMachine::~VirtualMachine()
{
  for (std::map<char *,addon,cmp_str>::iterator it = functions.begin();
       it != functions.end();++it)
  {
    delete it->first;
  }
}


void VirtualMachine::execute(Script script)
{
  Instruction * * instructionPtr = script.getInstructionPtr();
  Instruction const * instruction = *instructionPtr;


  while (instructionPtr != nullptr)
  {
    Instruction const * instruction = *instructionPtr;

    switch(instruction->code)
    {
    case op_jmp:
      instructionPtr = script.getInstructionPtr() + variables[instruction->args[0]];
      break;

    case op_jeq:
      if (variables[instruction->args[1]] == 0)
        instructionPtr = script.getInstructionPtr() + variables[instruction->args[0]];
      break;

    case op_jne:
      if (variables[instruction->args[1]] != 0)
        instructionPtr = script.getInstructionPtr() + variables[instruction->args[0]];
      break;

    case op_jlt:
      if (variables[instruction->args[1]] < 0)
        instructionPtr = script.getInstructionPtr() + variables[instruction->args[0]];
      break;

    case op_jle:
      if (variables[instruction->args[1]] <= 0)
        instructionPtr = script.getInstructionPtr() + variables[instruction->args[0]];
      break;

    case op_jgt:
      if (variables[instruction->args[1]] > 0)
        instructionPtr = script.getInstructionPtr() + variables[instruction->args[0]];
      break;

    case op_jge:
      if (variables[instruction->args[1]] >= 0)
        instructionPtr = script.getInstructionPtr() + variables[instruction->args[0]];
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
      instructionPtr = nullptr;
      break;
    }
  }

}


void VirtualMachine::registerAddon(addon newAddon,char * name)
{
  functions[name] = newAddon;
}


void VirtualMachine::dump()
{
  int i = 0;
  for (std::vector<int>::iterator it = variables.begin();it != variables.end(); ++it)
  {
    printf("variables[%d] = %d\n",i,*it);
    i++;
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
