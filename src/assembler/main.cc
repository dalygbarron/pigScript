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

  Instruction * * instruction = instructions->getInstructionPtr();
  printf("%d\n",(*instruction)->code);
  while (false)
  {
    printf("%d\n",(*instruction)->code);
    instruction++;

    if ((*instruction)->code == op_end)
    {
      break;
    }
  }

  return 0;
}
