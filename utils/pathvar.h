#ifndef PATHVAR_H
#define PATHVAR_H

struct pathNode
{
  char* parDir;
  struct pathNode* next;
};

char* setPath(char* cmd);

void appendPath(char* path, struct pathNode** head);

struct pathNode* retCmdLoc(char* cmd, struct pathNode* head);

#endif
