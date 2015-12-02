#include "ioPlugins.hh"

#include <stdio.h>

#include "VirtualMachine.hh"


static void readInt(uint8_t * args,int * variables)
{
  printf("enter an integer[%d]:",args[0]);
  scanf("%d",variables + args[0]);
}


static void writeInt(uint8_t * args,int * variables)
{
  printf("%d",variables[args[0]]);
}

static void writeString(uint8_t * args,int * variables)
{
  printf("%s",args);
}

static void writeNL(uint8_t * args,int * variables)
{
  printf("\n");
}


void ioPlugins_addAddons(VirtualMachine * vm)
{
  vm->registerAddon(&readInt,"readInt");
  vm->registerAddon(&writeInt,"writeInt");
  vm->registerAddon(&writeString,"writeString");
  vm->registerAddon(&writeNL,"writeNL");

}
