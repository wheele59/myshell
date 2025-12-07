#ifndef LOGGER_H
#define LOGGER_H

#include <sys/types.h>

void logger_init(void);
void log_command(pid_t pid, const char *cmd, int status);

#endif

