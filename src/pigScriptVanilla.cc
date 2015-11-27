//contains a virtual machine that runs pigscript without any plugin stuff


#include <stdio.h>

#include "Script.hh"
#include "VirtualMachine.hh"


int main(int argc,char * * argv)
{
  //make sure arguments are correct
  if (argc != 2)
  {
    printf("usage: pigScriptVanilla file.psc\n");
    return 0;
  }

  //load the script
  Script * script = new Script(argv[1]);

  //run it
  VirtualMachine vm;
  vm.execute(script);


  printf ("running complete\n");

  return 0;
}
