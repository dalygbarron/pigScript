#include "LabelManager.hh"

#include <stdint.h>
#include <map>
#include <vector>


using namespace std;


uint32_t LabelManager::registerPointer(char * token,uint16_t * labelPtr)
{
  labels[token].second.push_back(labelPtr);
}


uint32_t registerLabel(char * token,uint16_t address)
{
  labels[token].first = address;
}


void LabelManager::fillPointers()
{
  //TODO: shorten these gigantic type names somehow
  //iterate over all of the labels
  for (map<char *,AdressPointers,danylib_cmpstrptr>::iterator labelIterator =
       labels.begin();
       labelIterator != labels.end();
       ++labelIterator)
  {
    //get the stuff that is being iterated over
    uint16_t address = labelIterator->second.first;
    vector<uint16_t *> pointers = labelIterator->second.second;

    //iterate over all of the pointers to the label
    for (vector<uint16_t *>::iterator pointerIterator = pointers.begin();
         pointerIterator != pointers.end();++pointerIterator)
    {
      **pointerIterator = address;
    }
  }
}
