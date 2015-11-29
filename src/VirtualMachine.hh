//the virtual machine that runs the instructions


#ifndef VIRTUAL_MACHINE_H
#define VIRTUAL_MACHINE_H


#include <map>
#include <vector>
#include <cstring>
#include <stdint.h>

#include "danylib/danylib.hh"

#include "Instruction.hh"
#include "Script.hh"


#define N_VARIABLES 256





//the type of the function pointers that are called through the bytecode
typedef int (*addon)(uint8_t * args);


class VirtualMachine
{
public:
  //initialises the variables to 0
  VirtualMachine();

  //deletes stored function names
  ~VirtualMachine();

  //run a given script
  void execute(Script * scriptPtr);

  //register a function with the virtual machine
  //takes ownership of the name
  void registerAddon(addon newAddon,uint8_t * name);

private:
  //displays all of the current variables on the commandline
  void dump();
  //calls a function from within the bytecode
  void call(uint8_t * args);

  //the map of functions to their names so that scripts can call them
  std::map<uint8_t *,addon,danylib_cmpstrptr> functions;
  //where the running script's variables go
  int variables[N_VARIABLES];
};


#endif
