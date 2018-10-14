#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<fcntl.h>
#include "utils/cmdlist.h"
#include "utils/pathvar.h"
#include "extcmd/cmdalloc.h"
#include "features/redir.h"

int main(int argc, char* argv[])
{
  if(argc>2)
    {
      printf("Usage: ./hash [batch_file]");
      exit(1);
    }

  char *cmd = NULL;
  size_t bufLen = 0;

  printf(">hash ");

  struct pathNode* head = (struct pathNode*) malloc(sizeof(struct pathNode));
  head->parDir = "/bin/";
  head->next   = NULL;

  while(1)
    {
      bufLen = getline(&cmd, &bufLen, stdin);

      char* pos;
      if((pos=strchr(cmd, '\n')) != NULL)
        *pos = '\0';

      int errc = chooseCmd(cmd, &head);
      if(errc==0) //for external commands
        continue;

      char* temp = strdup(cmd);
      char* newPath = setPath(temp);//append path
      if(newPath!=NULL)
      {
        printf("%s\n", newPath);
        appendPath(newPath, &head);
        printf(">hash ");
        continue;
      }

      //redirection
      int isRedir = isRedirect(cmd);
      if(isRedir>1)
      {
        printf("Error: Multiple redirection symbols detected!!\n");
        printf(">hash ");
        continue;
      }
      else if(isRedir==1)
      {
        struct tokenInfo* splitCmd = outputRedirect(cmd);
        int spaces = spaceCount(splitCmd[1].commands[0]);
        if(spaces>=1)
        {
          printf("Error: Multiple files or spaces detected\n");
          printf(">hash ");
          continue;
        }
        else
        {
          int file = open(splitCmd[1].commands[0], O_CREAT | O_WRONLY | O_TRUNC, 0777);
          int current_out = dup(1);//file handle for stdout

          if(dup2(file, 1)<0)
          {
            printf("Error: Couldn't redirect output to file\n");
            printf(">hash ");
            continue;
          }
          int rc = fork();
          if(rc<0)
          {
            fprintf(stderr, "Something went horribly wrong!!\n");
            exit(1);
          }
          else if(rc==0)
          {
            struct pathNode* path = retCmdLoc(splitCmd[0].commands[0], head);
            if(path==NULL)
            {
              printf("\'%s\' command not found in the current path.\n Try adding the path of the command through: $PATH -a [path].\n", cmd);
              break;
            }
            char *s = concat(path->parDir, splitCmd[0].commands[0]);
        	  execv(s, splitCmd[0].commands);
        	  break;
          }
          else
          {
            wait(NULL);
            if(dup2(current_out, 1)<0)
            {
              fprintf(stderr, "Unable to reset output\n");
              exit(1);
            }
        	  printf(">hash ");
            continue;
          }
        }
      }


      int rc = fork();

      if(rc<0)
      	{
      	  fprintf(stderr, "Something went horribly wrong!!\n");
      	  exit(1);
      	}
      else if(rc==0)
      	{
          char* delimiter = " ";

      	  struct tokenInfo tI = tokenizeCmd(cmd, delimiter);

          struct pathNode* path = retCmdLoc(tI.commands[0], head);

          if(path==NULL)
          {
            printf("\'%s\' command not found in the current path.\n Try adding the path of the command through: $PATH -a [path].\n", cmd);
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
