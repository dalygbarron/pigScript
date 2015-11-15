#include "parser.hh"

#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <cstring>

#include "danylib/danylib.hh"

#include "../Script.hh"
#include "../Instruction.hh"


#define ARG_BUFFER_SIZE 2048


static char symbolise(std::vector<char *> * symbols,char * token)
{
  char i = 0;
  for (std::vector<char *>::iterator it = symbols->begin();
       it != symbols->end(); ++it)
  {
    //if it's already in the table
    if (strcmp(token,*it))
    {
      return i;
    }
    i++;
  }

  //create a new symbol
  symbols->push_back(token);

  //return it
  return symbols->size() - 1;
}


Script * parseTokens(std::vector<char *> * tokens)
{
  std::vector<char *> symbols;

  std::vector<Instruction> * instructions = new std::vector<Instruction>();
  int i = 0;

  while (i < tokens->size())
  {
    if (strcmp(tokens->at(i),"jmp") == 0)
    {
      instructions->emplace_back(op_jmp);
      i++;
    }

    else if (strcmp(tokens->at(i),"jeq") == 0)
    {
      char * args = new char;
      *args = symbolise(&symbols,tokens->at(i + 1));
      instructions->emplace_back(op_jeq,args);
      i += 2;
    }

    else if (strcmp(tokens->at(i),"jne") == 0)
    {
      char * args = new char;
      *args = symbolise(&symbols,tokens->at(i + 1));
      instructions->emplace_back(op_jne,args);
      i += 2;
    }

    else if (strcmp(tokens->at(i),"jlt") == 0)
    {
      char * args = new char;
      *args = symbolise(&symbols,tokens->at(i + 1));
      instructions->emplace_back(op_jlt,args);
      i += 2;
    }

    else if (strcmp(tokens->at(i),"jle") == 0)
    {
      char * args = new char;
      *args = symbolise(&symbols,tokens->at(i + 1));
      instructions->emplace_back(op_jle,args);
      i += 2;
    }

    else if (strcmp(tokens->at(i),"jgt") == 0)
    {
      char * args = new char;
      *args = symbolise(&symbols,tokens->at(i + 1));
      instructions->emplace_back(op_jgt,args);
      i += 2;
    }

    else if (strcmp(tokens->at(i),"jge") == 0)
    {
      char * args = new char;
      *args = symbolise(&symbols,tokens->at(i + 1));
      instructions->emplace_back(op_jge,args);
      i += 2;
    }

    else if (strcmp(tokens->at(i),"call") == 0)
    {
      OpCode code = op_call;
      int nArgs = atoi(tokens->at(i + 1));
      char args[ARG_BUFFER_SIZE];

      //put all the arguments into the argument array
      int placement = 0;
      for (int argI = 0;argI < nArgs;argI++)
      {
        char * arg = tokens->at(i + 2 + argI);

        //if it's a string literal
        if (arg[0] == '\"')
        {
          int letterI = 1;

          while (arg[letterI] != '\0')
          {
            args[placement] = arg[letterI];
            placement++;
            letterI++;
          }
          arg[placement] = '\0';
          placement++;
        }

        //if it's a variable
        else
        {
          args[placement] = symbolise(&symbols,arg);
          placement++;
        }
      }

      //now put the instruction in
      instructions->emplace_back(op_call,danylib_fit(args));

      //get it past all the arguments to the next instruction token
      i += nArgs + 1;
    }

    else if (strcmp(tokens->at(i),"set") == 0)
    {
      char * args = new char[2];
      args[0] = atoi(tokens->at(i + 1));
      args[1] = symbolise(&symbols,tokens->at(i + 2));

      instructions->emplace_back(op_set,args);

      i += 3;
    }

    else if (strcmp(tokens->at(i),"add") == 0)
    {
      char * args = new char[2];
      args[0] = symbolise(&symbols,tokens->at(i + 1));
      args[1] = symbolise(&symbols,tokens->at(i + 2));
      args[2] = symbolise(&symbols,tokens->at(i + 3));

      instructions->emplace_back(op_set,args);

      i += 4;
    }

    else if (strcmp(tokens->at(i),"dump") == 0)
    {
      instructions->emplace_back(op_set);

      i++;
    }

    //if it's not a valid thingo
    else
    {
      printf("%s is not a valid instruction\n",tokens->at(i));
      i++;
    }
  }
  return new Script(instructions);
}
