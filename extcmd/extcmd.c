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

void execPath(char* cmd, struct pathNode** head)
{
  struct tokenInfo p = tokenizeCmd(cmd, " ");
  int i;

  struct pathNode* temp = (struct pathNode*)malloc(sizeof(struct pathNode));
  temp->parDir = p.commands[1];
  temp->next = NULL;

  for(i=2; i<p.noc-1; i++)
  {
    printf("%d\n", i);
    appendPath(p.commands[i], &temp);
  }
  *head = temp;
  printf(">hash ");
}
