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
      instructionIndex = danylib_bytesToValue<uint32_t>(instruction->args) - 1;
      break;

    case op_jeq:
      if (variables[instruction->args[LABEL_SIZE]] == 0)
        instructionIndex = danylib_bytesToValue<uint32_t>(instruction->args) - 1;
      break;

    case op_jne:
      if (variables[instruction->args[LABEL_SIZE]] != 0)
        instructionIndex = danylib_bytesToValue<uint32_t>(instruction->args) - 1;
      break;

    case op_jlt:
      if (variables[instruction->args[LABEL_SIZE]] < 0)
        instructionIndex = danylib_bytesToValue<uint32_t>(instruction->args) - 1;
      break;

    case op_jle:
      if (variables[instruction->args[LABEL_SIZE]] <= 0)
        instructionIndex = danylib_bytesToValue<uint32_t>(instruction->args) - 1;
      break;

    case op_jgt:
      if (variables[instruction->args[LABEL_SIZE]] > 0)
        instructionIndex = danylib_bytesToValue<uint32_t>(instruction->args) - 1;
      break;

    case op_jge:
      if (variables[instruction->args[LABEL_SIZE]] >= 0)
        instructionIndex = danylib_bytesToValue<uint32_t>(instruction->args) - 1;
      break;

    case op_call:
      call(instruction->args);
      break;

    case op_set:
      variables[instruction->args[CONST_SIZE]] = danylib_bytesToValue<int>(instruction->args);
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
      instructionIndex = -2;
      break;
    }

    instructionIndex++;
  }

}


void VirtualMachine::registerAddon(addon newAddon,char const * name)
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


void VirtualMachine::call(uint8_t * args)
{
  if (functions.count((char *)(args + 2)) == 1)
  {
    //skip the length of arguments and function name
    int start = 2;
    while (args[start] != '\0')
    {
      start++;
    }
    functions[(char *)(args + 2)](args + start + 1,variables);
  }
  else
  {
    printf("%s is not a registered function, but continuing with execution\n",args + 2);
  }
}
