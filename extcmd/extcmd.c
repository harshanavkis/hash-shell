#include "extcmd.h"

void execExit()
{
  exit(0);
}

void execCd(char* cmd)
{
  struct tokenInfo cd = tokenizeCmd(cmd, " ");
  int errcd = chdir(cd.commands[1]);
  if(errcd==0)
  {
    printf(">hash ");
  }
  else
  {
    printf("Unable to change directory. %s:directory doesn't exist\n", cd.commands[1]);
    printf(">hash ");
  }
}
