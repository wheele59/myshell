#ifndef EXECUTE_H
#define EXECUTE_H

#include "parse.h"

int execute_command(Command *cmd, const char *raw_line);

#endif

