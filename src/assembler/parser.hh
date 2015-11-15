//parses a bunch of tokens and turns them into instructions
//also converts symbols to numbers


#ifndef PARSER_H
#define PARSER_H


#include <vector>

#include "../Script.hh"


//parses some tokens into a script
Script * parseTokens(std::vector<char *> * tokens);


#endif
