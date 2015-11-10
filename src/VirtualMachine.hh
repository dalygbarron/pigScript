//the virtual machine that runs the instructions


#ifndef VIRTUAL_MACHINE_H
#define VIRTUAL_MACHINE_H


#include <map>
#include <vector>
#include <cstring>
#include <stdint.h>

#include "Instruction.hh"
#include "Script.hh"


//this is so that I can use a c string as a map key
struct cmp_str
{
   bool operator()(char const * a, char const * b)
   {
      return std::strcmp(a, b) < 0;
   }
};


//the type of the function pointers that are called through the bytecode
typedef int (*addon)(uint32_t * args,int nArgs);


class VirtualMachine
{
public:
  //deletes stored function names
  ~VirtualMachine();

  //run a given script
  void execute(Script script);

  //register a function with the virtual machine
  //takes ownership of the name
  void registerAddon(addon newAddon,char const * name);

private:
  //the map of functions to their names so that scripts can call them
  std::map<char *,addon,cmp_str> functions;
  //where the running script's variables go
  std::vector<int> variables;
};


#endif
