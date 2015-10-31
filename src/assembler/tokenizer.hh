//reads in a file or a string and turns it into an array of strings for each token


#ifndef TOKENIZER_H
#define TOKENIZER_H


#include <stdio.h>


//turn a string into tokens
char * * tokenize(char * data);

//turn a file into tokens
char * * tokenize(FILE * dataFile);

#endif
