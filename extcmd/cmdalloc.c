#include "cmdalloc.h"
#include <string.h>

int chooseCmd(char* cmd, struct pathNode** head)
{
  char* temp    = cmd;
  char* exitCmd = "exit";
  char* cdCmd   = "cd";
  char* pathCmd = "path";
  if(strncmp(temp, exitCmd, 4)==0)
  {
    execExit();
    return 0;
  }
  else if(strncmp(temp, cdCmd, 2)==0)
  {
    execCd(temp);
    return 0;
  }
  else if(strncmp(temp, pathCmd, 4)==0)
  {
    execPath(temp, head);
    return 0;
  }
  return 1;
}
