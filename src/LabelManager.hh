//manages labels and can then also write them to a file


#ifndef LABEL_MANAGER_H
#define LABEL_MANAGER_H


#include <stdint.h>
#include <utility>
#include <map>
#include <vector>

#include "danylib/danylib.hh"


using namespace std;


typedef pair<uint16_t,vector<uint16_t *> > AdressPointers;


class LabelManager
{
public:
  //registers a label pointer to be filled with the address of the label at a later time
  uint32_t registerPointer(char * token,uint16_t * labelPtr);

  //tell the label manager the address of a certain label
  uint32_t registerLabel(char * token,uint16_t address);

  //put the address of all the labels into all their pointers
  void fillPointers();

private:
  map<char *,AdressPointers,danylib_cmpstrptr> * labels;
};


#endif
