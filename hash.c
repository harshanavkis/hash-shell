#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include "utils/cmdlist.h"
#include "utils/pathvar.h"

int main(int argc, char* argv[])
{
  if(argc>2)
    {
      printf("Usage: ./hash [batch_file]");
      exit(1);
    }

  char* exitCmd = "exit\n";
  char *cmd = NULL;
  size_t bufLen = 0;

  printf(">hash ");

  char *path = "/bin/";
  struct pathNode* head = (struct pathNode*) malloc(sizeof(struct pathNode));
  head->parDir = path;
  head->next   = NULL;

  while(1)
    {
      bufLen = getline(&cmd, &bufLen, stdin);

      if(strncmp(exitCmd, cmd, 5)==0)
	exit(0);

      char* pos;
      if((pos=strchr(cmd, '\n')) != NULL)
        *pos = '\0';

      int rc = fork();

      if(rc<0)
	{
	  fprintf(stderr, "Unable to create child process\n");
	  exit(1);
	}
      else if(rc==0)
	{
    char* delimiter = " ";

	  struct tokenInfo tI = tokenizeCmd(cmd, delimiter);

    struct pathNode* path = retCmdLoc(tI.commands[0], head);

    if(path==NULL)
    {
      printf("\'%s\' command not found in the current path.\n Try adding the path of the command through: $PATH -a [cmd].\n", cmd);
      break;
    }

    char *s = concat(path->parDir, tI.commands[0]);
	  execv(s, tI.commands);
	  break;
	}
      else
	{
	  wait(NULL);
	  printf(">hash ");
	}
    }
}
