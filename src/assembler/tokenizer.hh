//reads in a file or a string and turns it into an array of strings for each token


#ifndef TOKENIZER_H
#define TOKENIZER_H


#include <vector>
#include <stdio.h>


//turn a string into tokens
std::vector<char *> * tokenize(char const * data);

//turn a file into tokens
std::vector<char *> * tokenize(FILE * dataFile);

#endif
