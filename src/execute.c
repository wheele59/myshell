#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "execute.h"
#include "signals.h"
#include "logger.h"

static void setup_redirection(Command *cmd) {
    if (cmd->input_file) {
        int fd = open(cmd->input_file, O_RDONLY);
        dup2(fd, STDIN_FILENO);
        close(fd);
    }

    if (cmd->output_file) {
        int flags = O_WRONLY | O_CREAT | (cmd->append ? O_APPEND : O_TRUNC);
        int fd = open(cmd->output_file, flags, 0644);
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
}

int execute_command(Command *cmd, const char *raw_line) {
    if (cmd->pipe_argv) {
        int fd[2];
        pipe(fd);

        pid_t left = fork();
        if (left == 0) {
            restore_signals();
            dup2(fd[1], STDOUT_FILENO);
            close(fd[0]);
            close(fd[1]);
            execvp(cmd->argv[0], cmd->argv);
            perror("execvp");
            exit(1);
        }

        pid_t right = fork();
        if (right == 0) {
            restore_signals();
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            close(fd[1]);
            execvp(cmd->pipe_argv[0], cmd->pipe_argv);
            perror("execvp");
            exit(1);
        }

        close(fd[0]);
        close(fd[1]);

        int s1, s2;
        waitpid(left, &s1, 0);
        waitpid(right, &s2, 0);

        int status = WIFEXITED(s2) ? WEXITSTATUS(s2) : -1;
        log_command(right, raw_line, status);
        return 0;
    }

    pid_t pid = fork();
    if (pid == 0) {
        restore_signals();
        setup_redirection(cmd);
        execvp(cmd->argv[0], cmd->argv);
        perror("execvp");
        exit(1);
    }

    if (cmd->background) {
        printf("[bg] started pid %d\n", (int)pid);
        log_command(pid, raw_line, -1);
    } else {
        int status;
        waitpid(pid, &status, 0);
        int exit_status = WIFEXITED(status) ? WEXITSTATUS(status) : -1;
        log_command(pid, raw_line, exit_status);
    }

    return 0;
}

