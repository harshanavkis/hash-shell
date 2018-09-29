#ifndef CMDLIST_H_
#define CMDLIST_H_

struct tokenInfo
{
  char** commands;
  int noc;
};

struct tokenInfo tokenizeCmd(char* cmd, char* delimiter);

char* concat(const char *s1, const char *s2);

#endif
