#include "redir.h"

int isRedirect(char* cmd)
{
  int count  = 0;
  int cmdlen = strlen(cmd);
  int i;
  for(i=0; i<cmdlen; i++)
  {
    if(cmd[i]=='>')
    {
      count++;
    }
  }
  return count;
}

struct tokenInfo* outputRedirect(char* cmd)
{
  int cmdlen = strlen(cmd);
  int index=0;
  int i;
  for(i=0; i<cmdlen; i++)
  {
    if(cmd[i]=='>')
    {
      index = i;
      break;
    }
  }
  char* cmdOpt = (char*)malloc(sizeof(char)*(index));
  char* outputFile = (char*)malloc(sizeof(char)*(cmdlen-index));
  strncpy(cmdOpt, cmd, index-1);
  cmdOpt[index] = '\0';

  int j=0;
  for(i=index+2; i<cmdlen; i++)
  {
    outputFile[j] = cmd[i];
    j++;
  }
  outputFile[cmdlen-index] = '\0';

  struct tokenInfo cmdtI  = tokenizeCmd(cmdOpt, " ");
  struct tokenInfo filetI = {.commands=&outputFile, .noc=0};

  struct tokenInfo* redirectToken = (struct tokenInfo*)malloc(sizeof(struct tokenInfo)*2);
  redirectToken[0] = cmdtI;
  redirectToken[1] = filetI;
  return redirectToken;
}
