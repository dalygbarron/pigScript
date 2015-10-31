#include "tokenizer.hh"

#include <stdio.h>
#include <vector>


#define BUFFER_LENGTH 1024


using namespace std;


char * fit(char * data)
{
  int length = 0;
  while (data[length] != '\0')
    length++;

  char * fittedData = new char[length];
  for (int i = 0;i < length;i++)
  {
    fittedData[i] = data[i]
  }

  return fittedData;
}


vector<char *> * tokenize(char * data)
{
  vector<char *> tokens;
  char buffer[];
  bool string = false;
  bool 

  int i = 0;
  while (data[i] != '\0')
  {


    i++;
  }
}

vector<char *> * tokenize(FILE * dataFile)
{

}
