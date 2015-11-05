//parses a bunch of tokens and turns them into instructions
//also converts symbols to numbers


#ifndef PARSER_H
#define PARSER_H


#include <vector>

#include "../Script.hh"


class Parser
{
public:
  //gets rid of the symbol table
  ~Parser();

  //parses some tokens into a script
  Script * parseTokens(std::vector<char *> * tokens);

private:
  //turn a symbol into it's number, whether or not it already exists
  int symbolise(char * token);

  //all of the currently existing symbols
  std::vector<char *> symbols;
};


#endif
