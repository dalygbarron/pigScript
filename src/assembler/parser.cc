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


static uint8_t symbolise(std::vector<char *> * symbols,char * token)
{
  //search for it in the table
  uint8_t i = 0;
  for (std::vector<char *>::iterator it = symbols->begin();
       it != symbols->end(); ++it)
  {
    //if it's already in the table
    if (strcmp(token,*it) == 0)
    {
      printf("%s is already %d\n",token,i);
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
  LabelManager labelManager;

  Script * script = new Script();

  int i = 0;
  while (i < tokens->size())
  {
    OpCode code = stringToOpCode(tokens->at(i));

    //if it's a jump
    if (code == op_jmp)
    {
      uint8_t * args = new uint8_t[sizeof(Label)];
      labelManager.registerPointer(tokens->at(i + 1),args);
      script->instructions.push_back(new Instruction(code,args));
      i += 2;
    }

    //if it's a conditional jump of some description
    else if ((code == op_jeq) || (code == op_jne) || (code == op_jlt) ||
             (code == op_jle) || (code == op_jgt) || (code == op_jge))
    {
      uint8_t * args = new uint8_t[sizeof(Label) + 1];
      labelManager.registerPointer(tokens->at(i + 1),args);
      args[sizeof(Label)] = symbolise(&symbols,tokens->at(i + 2));
      script->instructions.push_back(new Instruction(code,args));
      i += 3;
    }

    //if it's a call instruction
    else if (code == op_call)
    {
      OpCode code = op_call;
      int nArgs = atoi(tokens->at(i + 1));

      uint8_t args[ARG_BUFFER_SIZE];

      //put all the arguments into the argument array
      int placement = 2;
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
          args[placement] = '\0';
          placement++;
        }

        //if it's a variable
        else
        {
          args[placement] = symbolise(&symbols,arg);
          placement++;
        }
      }
      //put the length of the arguments into first place
      args[0] = (char)(placement & 0xFF);
      args[1] = (char)((placement >> 8) & 0xFF);

      //now put the instruction in
      script->instructions.push_back(new Instruction(code,danylib_fitToLength<uint8_t>(args,placement)));

      //get it past all the arguments to the next instruction token
      i += nArgs + 2;
    }

    //if it's a set instructoin
    else if (code == op_set)
    {
      uint8_t * args = new uint8_t[sizeof(uint32_t) + 1];
      danylib_valueToBytes<uint32_t>(atoi(tokens->at(i + 1)),args);
      args[sizeof(uint32_t)] = symbolise(&symbols,tokens->at(i + 2));
      script->instructions.push_back(new Instruction(code,args));
      i += 3;
    }

    //if it's a move instructoin
    else if (code == op_move)
    {
      uint8_t * args = new uint8_t[2];
      args[0] = symbolise(&symbols,tokens->at(i + 1));
      args[1] = symbolise(&symbols,tokens->at(i + 2));
      script->instructions.push_back(new Instruction(code,args));
      i += 3;
    }

    //if it's an add instruction
    else if ((code == op_add) || (code == op_sub))
    {
      uint8_t * args = new uint8_t[2];
      args[0] = symbolise(&symbols,tokens->at(i + 1));
      args[1] = symbolise(&symbols,tokens->at(i + 2));
      args[2] = symbolise(&symbols,tokens->at(i + 3));
      script->instructions.push_back(new Instruction(code,args));
      i += 4;
    }

    //if it's a dump instruction
    else if ((code == op_dump) || (code == op_end))
    {
      script->instructions.push_back(new Instruction(code));
      i++;
    }

    //if it's a label
    else if (code == label)
    {
      labelManager.registerLabel(tokens->at(i + 1),script->instructions.size());
      i += 2;
    }

    //if it's not a valid thingo
    else
    {
      printf("%s is not a valid instruction\n",tokens->at(i));
      i++;
    }
  }

  //put the values into the label pointers
  labelManager.fillPointers();

  return script;
}
