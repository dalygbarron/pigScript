#include "parser.hh"

#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <cstring>

#include "danylib/danylib.hh"

#include "../Script.hh"
#include "../Instruction.hh"
#include "LabelManager.hh"


#define ARG_BUFFER_SIZE 2048


static uint8_t symbolise(Script const * script,std::vector<uint8_t *> * symbols,uint8_t * token)
{
  //search for it in the table
  uint8_t i = 0;
  for (std::vector<uint8_t *>::iterator it = symbols->begin();
       it != symbols->end(); ++it)
  {
    //if it's already in the table
    if (strcmp(token,*it) == 0)
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


Script * parseTokens(std::vector<uint8_t *> * tokens)
{
  std::vector<uint8_t *> symbols;
  LabelManager labelManager;

  Script * script = new Script();

  int i = 0;
  while (i < tokens->size())
  {
    if (strcmp(tokens->at(i),"jmp") == 0)
    {
      uint8_t * args = new uint8_t[sizeof(uint32_t)];
      script->instructions.push_back(new Instruction(op_jmp));
      i++;
    }

    else if (strcmp(tokens->at(i),"jeq") == 0)//TODO: join all the conditional jumps
    {
      uint8_t * args = new uint8_t;
      *args = symbolise(&symbols,tokens->at(i + 1));
      script->instructions.push_back(new Instruction(op_jeq,args));
      i += 2;
    }

    else if (strcmp(tokens->at(i),"jne") == 0)
    {
      uint8_t * args = new uint8_t;
      *args = symbolise(&symbols,tokens->at(i + 1));
      script->instructions.push_back(new Instruction(op_jne,args));
      i += 2;
    }

    else if (strcmp(tokens->at(i),"jlt") == 0)
    {
      uint8_t * args = new uint8_t;
      *args = symbolise(&symbols,tokens->at(i + 1));
      script->instructions.push_back(new Instruction(op_jlt,args));
      i += 2;
    }

    else if (strcmp(tokens->at(i),"jle") == 0)
    {
      uint8_t * args = new uint8_t;
      *args = symbolise(&symbols,tokens->at(i + 1));
      script->instructions.push_back(new Instruction(op_jle,args));
      i += 2;
    }

    else if (strcmp(tokens->at(i),"jgt") == 0)
    {
      uint8_t * args = new uint8_t;
      *args = symbolise(&symbols,tokens->at(i + 1));
      script->instructions.push_back(new Instruction(op_jgt,args));
      i += 2;
    }

    else if (strcmp(tokens->at(i),"jge") == 0)
    {
      uint8_t * args = new uint8_t;
      *args = symbolise(&symbols,tokens->at(i + 1));
      script->instructions.push_back(new Instruction(op_jge,args));
      i += 2;
    }

    else if (strcmp(tokens->at(i),"call") == 0)
    {
      OpCode code = op_call;
      int nArgs = atoi(tokens->at(i + 1));

      uint8_t args[ARG_BUFFER_SIZE];

      //put all the arguments into the argument array
      int placement = 2;
      for (int argI = 0;argI < nArgs;argI++)
      {
        uint8_t * arg = tokens->at(i + 2 + argI);

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
          args[placement] = symbolise(script,&symbols,arg);
          placement++;
        }
      }
      //put the length of the arguments into first place
      args[0] = (uint8_t)(placement & 0xFF);
      args[1] = (uint8_t)((placement >> 8) & 0xFF);

      printf("placement:%d\n",placement);

      //now put the instruction in
      script->instructions.push_back(new Instruction(op_call,danylib_fitToLength(args,placement)));

      //get it past all the arguments to the next instruction token
      i += nArgs + 2;
    }

    else if (strcmp(tokens->at(i),"set") == 0)
    {
      uint8_t * args = new uint8_t[2];
      args[0] = atoi(tokens->at(i + 1));
      args[1] = symbolise(&symbols,tokens->at(i + 2));

      script->instructions.push_back(new Instruction(op_set,args));

      i += 3;
    }

    else if (strcmp(tokens->at(i),"add") == 0)
    {
      uint8_t * args = new uint8_t[2];
      args[0] = symbolise(&symbols,tokens->at(i + 1));
      args[1] = symbolise(&symbols,tokens->at(i + 2));
      args[2] = symbolise(&symbols,tokens->at(i + 3));

      script->instructions.push_back(new Instruction(op_add,args));

      i += 4;
    }

    else if (strcmp(tokens->at(i),"dump") == 0)
    {
      script->instructions.push_back(new Instruction(op_dump));
      i++;
    }

    //if it's not a valid thingo
    else
    {
      printf("%s is not a valid instruction\n",tokens->at(i));
      i++;
    }
  }
  return script;
}
