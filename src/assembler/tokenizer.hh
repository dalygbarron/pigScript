//reads in a file or a string and turns it into an array of strings for each token


#ifndef TOKENIZER_H
#define TOKENIZER_H


#include <vector>
#include <stdio.h>


//turn a string into tokens
std::vector<uint8_t *> * tokenize(uint8_t const * data);

//turn a file into tokens
std::vector<uint8_t *> * tokenize(FILE * dataFile);

#endif
