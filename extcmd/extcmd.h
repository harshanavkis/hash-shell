#ifndef EXTCMD_H
#define EXTCMD_H

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../utils/cmdlist.h"
#include "../utils/pathvar.h"

void execExit();
void execCd(char* cmd);
// void execPath(char* cmd, struct pathNode** head);

#endif
