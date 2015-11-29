#include "Script.hh"

#include <stdio.h>
#include <vector>


Script::Script()
{
  //does nothing
}


Script::Script(char const * filename)
{
  FILE * inFile = fopen(filename,"rb");
  //test if the file has been opened right
  if (!inFile)
  {
    printf("couldn't open file %s\n",filename);
  }
  //write in the number of instructions
  uint32_t nInstructions;
  fread(&nInstructions,sizeof(uint32_t),1,inFile);
  //read each instruction
  for (int i = 0;i < nInstructions;i++)
  {
    Instruction * ins = new Instruction(inFile);
    instructions.push_back(ins);
  }
  //close the file again
  fclose(inFile);
}


Script::~Script()
{
  //TODO: delete the instructions
}


Instruction * Script::operator[](int index)
{
  return instructions[index];
}


void Script::toFile(char const * filename)
{
  FILE * outFile = fopen(filename,"wb");
  //test if the file has been opened right
  if (!outFile)
  {
    printf("couldn't open file %s\n",filename);
  }
  //write in the number of instructions
  int nInstructions = instructions.size();
  fwrite(&nInstructions,sizeof(uint32_t),1,outFile);
  //write in each instruction
  for (int i = 0;i < instructions.size();i++)
  {
    instructions[i]->toFile(outFile);
  }
  //close the file again
  fclose(outFile);
}


int Script::size()
{
  return instructions.size();
}
