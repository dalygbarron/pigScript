#include <stdio.h>
#include <vector>

#include "tokenizer.hh"


int main(int argc,char * * argv)
{
  printf("%s\n",argv[1]);

  FILE * dataFile = fopen(argv[1],"r");

  std::vector<char *> * tokens = tokenize(dataFile);

  for (int i = 0;i < tokens->size();i++)
  {
    printf("%s\n",tokens->at(i));
  }

  return 0;
}
