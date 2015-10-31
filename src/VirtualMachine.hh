//the virtual machine that runs the instructions


#ifndef VIRTUAL_MACHINE_H
#define VIRTUAL_MACHINE_H


#include <map>
#include <vector>

#include "Instruction.h"


class VirtualMachine
{
public:
  //run a given script
  void execute(Script script);

  //register a function with the virtual machine
  void register(int (func*)(void * args,int nArgs),char const * name);

private:
  //the map of functions to their names so that scripts can call them
  std::map<char const *,int (func*)(void * args,int nArgs)> functions;
  //where the running script's variables go
  std::vector<int> variables(10);
};


#endif
