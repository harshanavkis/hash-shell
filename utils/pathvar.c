#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include "pathvar.h"
#include "cmdlist.h"

char* setPath(char* cmd)
{
  char* delimiter = " "; //you can do better
  char* temp = strdup(cmd);
  char* context;
  char *token = strtok_r(temp, delimiter, &context);
  if(strcmp(token, "$PATH")==0)
    {
      char* last = strtok_r(NULL, delimiter, &context);
      last       = strtok_r(NULL, delimiter, &context);
      return last;
    }
  else
    {
      return NULL;
    }
}

void appendPath(char* path, struct pathNode** head)
{
  struct pathNode* newPath = (struct pathNode*)malloc(sizeof(struct pathNode));
  newPath->parDir = path;
  newPath->next   = NULL;

  struct pathNode* last = *head;
  while (last->next != NULL)
   last = last->next;
  last->next = newPath;
}

struct pathNode* retCmdLoc(char* cmd, struct pathNode* head)
{
  struct pathNode* ptr = head;

  while(ptr!=NULL)
  {
    char* s = concat(ptr->parDir, cmd);
    int acc = access(s, X_OK);
    free(s);
    if(acc==0)
    {
      return ptr;
    }
    ptr = ptr->next;
  }
  return ptr;
}
