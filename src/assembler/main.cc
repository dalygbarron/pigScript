#include <stdio.h>
#include <vector>

#include "tokenizer.hh"
#include "parser.hh"
#include "../Script.hh"


int main(int argc,char * * argv)
{
  FILE * dataFile = fopen(argv[1],"r");

  std::vector<char *> * tokens = tokenize(dataFile);

  fclose(dataFile);

  Script * instructions = parseTokens(tokens);

  instructions->toFile("thots.psc");

  Script * moreInstructions = new Script("thots.psc");

  moreInstructions->toFile("moreThots.psc");

  return 0;
}
