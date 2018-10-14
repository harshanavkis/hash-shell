#ifndef REDIR_H
#define REDIR_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../utils/cmdlist.h"

int isRedirect(char* cmd);
struct tokenInfo* outputRedirect(char* cmd);

#endif
