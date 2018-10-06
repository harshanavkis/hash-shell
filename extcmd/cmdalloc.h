#ifndef CMDALLOC_H
#define CMDALLOC_H

#include "extcmd.h"
#include "../utils/cmdlist.h"
#include "../utils/pathvar.h"

int chooseCmd(char* cmd, struct pathNode** head);

#endif
