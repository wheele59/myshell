#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include "logger.h"

static int log_fd = -1;

void logger_init(void) {
    log_fd = open("myshell.log", O_WRONLY | O_CREAT | O_APPEND, 0644);
}

void log_command(pid_t pid, const char *cmd, int status) {
    if (log_fd < 0 || !cmd) return;

    char buf[512];
    int len = snprintf(buf, sizeof(buf),
                       "[pid=%d] cmd=\"%s\" status=%d\n",
                       (int)pid, cmd, status);
    if (len > 0) write(log_fd, buf, len);
}

