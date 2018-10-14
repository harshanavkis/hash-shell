#include <string.h>
#include<stdlib.h>
#include<stdio.h>
#include "cmdlist.h"

struct tokenInfo tokenizeCmd(char* cmd, char* delimiter)
{
  char* temp = strdup(cmd);
  char *token = strtok(cmd, delimiter);
  int count = 0;

  struct tokenInfo tI;

  while(token != NULL)
    {
      token = strtok(NULL, delimiter);
      count++;
    }
  tI.noc = count;
  char** commands;
  commands = malloc((tI.noc+1)*sizeof(char*));

  token = strtok(temp, delimiter);
  int i = 0;

  while(token != NULL)
  {
    commands[i] = token;
    i++;
    token = strtok(NULL, delimiter);
  }

  commands[i] = NULL;

  tI.commands = commands;

  return tI;
}

char* concat(const char *s1, const char *s2)
{
  char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
  if(result == NULL)
  {
    fprintf(stderr, "Unable to create commands\n");
    exit(1);
  }
  strcpy(result, s1);
  strcat(result, s2);
  return result;
}

int spaceCount(char* file)
{
  int count = 0;
  int len   = strlen(file);
  int i;
  for(i=0; i<len; i++)
  {
    if(file[i]==' ')
    {
      count++;
    }
  }
  return count;
}
