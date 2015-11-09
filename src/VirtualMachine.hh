//the virtual machine that runs the instructions


#ifndef VIRTUAL_MACHINE_H
#define VIRTUAL_MACHINE_H


#include <map>
#include <vector>

#include "Instruction.hh"
#include "Script.hh"


class VirtualMachine
{
public:
  //run a given script
  void execute(Script script);

  //register a function with the virtual machine
  void register(AddOn * newAddOn,char const * name);

private:
  //the map of functions to their names so that scripts can call them
  std::map<char const *,AddOn> functions;
  //where the running script's variables go
  std::vector<int> variables();
};


#endif
