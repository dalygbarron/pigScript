#include "Parser.hh"

#include <vector>
#include <stdio.h>
#include <cstring>

#include "../Script.hh"
#include "../Instruction.hh"





Parser::~Parser()
{
  for (std::vector<char *>::iterator it = symbols.begin();
       it != symbols.end(); ++it)
  {
    delete *it;
  }
}


Script * Parser::parseTokens(std::vector<char *> * tokens)
{
  std::vector<Instruction> * instructions = new std::vector<Instruction>();
  int i = 0;

  while (i < tokens->size())
  {
    if (strcmp(tokens->at(i),"jmp"))
    {
      instructions->emplace_back(op_jmp,new uint32_t,0);
      i++;
    }

    else if (strcmp(tokens->at(i),"jeq"))
    {
      uint32_t * args = new uint32_t;
      *args = symbolise(tokens->at(i + 1));
      instructions->emplace_back(op_jeq,args,1);
      i += 2;
    }

    else if (strcmp(tokens->at(i),"jne"))
    {
      uint32_t * args = new uint32_t;
      *args = symbolise(tokens->at(i + 1));
      instructions->emplace_back(op_jne,args,1);
      i += 2;
    }

    else if (strcmp(tokens->at(i),"jlt"))
    {
      uint32_t * args = new uint32_t;
      *args = symbolise(tokens->at(i + 1));
      instructions->emplace_back(op_jlt,args,1);
      i += 2;
    }

    else if (strcmp(tokens->at(i),"jle"))
    {
      uint32_t * args = new uint32_t;
      *args = symbolise(tokens->at(i + 1));
      instructions->emplace_back(op_jle,args,1);
      i += 2;
    }

    else if (strcmp(tokens->at(i),"jgt"))
    {
      uint32_t * args = new uint32_t;
      *args = symbolise(tokens->at(i + 1));
      instructions->emplace_back(op_jgt,args,1);
      i += 2;
    }

    else if (strcmp(tokens->at(i),"jge"))
    {
      uint32_t * args = new uint32_t;
      *args = symbolise(tokens->at(i + 1));
      instructions->emplace_back(op_jge,args,1);
      i += 2;
    }

    else if (strcmp(tokens->at(i),"call"))
    {
      OpCode code = op_call;


    }
  }
}


int Parser::symbolise(char * token)
{
  int i = 0;
  for (std::vector<char *>::iterator it = symbols.begin();
       it != symbols.end(); ++it)
  {
    //if it's already in the table
    if (strcmp(token,*it))
    {
      return i;
    }
    i++;
  }

  //create a new symbol
  symbols.push_back(token);

  //return it
  return symbols.size() - 1;
}
