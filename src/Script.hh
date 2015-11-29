//basically just a collection of instructions to be executed


#ifndef SCRIPT_H
#define SCRIPT_H


#include <vector>

#include "Instruction.hh"


class Script
{
public:
  //create a blank script
  Script();

  //create a script from a file
  Script(uint8_t const * filename);

  //destroy the script and it's instructions
  ~Script();

  //get an instruction at a specific point in the script
  Instruction * operator[](int index);

  //writes the script into a file
  void toFile(uint8_t const * filename);

  //gives you the length of the script
  int size();

  //let's the parsing thingo access the instructions
  friend Script * parseTokens(std::vector<uint8_t *> * tokens);

private:
  //the instructions that it is made up of
  std::vector<Instruction *> instructions;
};


#endif
