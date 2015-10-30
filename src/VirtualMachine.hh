//the virtual machine that runs the instructions


#ifndef VIRTUAL_MACHINE_H
#define VIRTUAL_MACHINE_H


#include <vector>

#include "Instruction.h"


class VirtualMachine
{
public:


private:
  //the instructions that it is currently to run
  std::vector<Instruction> instructions;  
};


#endif
