#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"

#define MAX_TOKENS 128

Command *parse_line(char *line) {
    Command *cmd = malloc(sizeof(Command));
    if (!cmd) return NULL;

    cmd->argv = malloc(sizeof(char *) * MAX_TOKENS);
    cmd->pipe_argv = NULL;
    cmd->input_file = NULL;
    cmd->output_file = NULL;
    cmd->append = 0;
    cmd->background = 0;

    int argc = 0;
    char *token = strtok(line, " \t\n");

    while (token) {
        if (strcmp(token, "&") == 0) {
            cmd->background = 1;
        } else if (strcmp(token, "|") == 0) {
            cmd->pipe_argv = malloc(sizeof(char *) * MAX_TOKENS);
            int p = 0;
            token = strtok(NULL, " \t\n");
            while (token) {
                cmd->pipe_argv[p++] = strdup(token);
                token = strtok(NULL, " \t\n");
            }
            cmd->pipe_argv[p] = NULL;
            break;
        } else if (strcmp(token, "<") == 0) {
            token = strtok(NULL, " \t\n");
            if (token) cmd->input_file = strdup(token);
        } else if (strcmp(token, ">") == 0) {
            token = strtok(NULL, " \t\n");
            if (token) {
                cmd->output_file = strdup(token);
                cmd->append = 0;
            }
        } else if (strcmp(token, ">>") == 0) {
            token = strtok(NULL, " \t\n");
            if (token) {
                cmd->output_file = strdup(token);
                cmd->append = 1;
            }
        } else {
            cmd->argv[argc++] = strdup(token);
        }
        token = strtok(NULL, " \t\n");
    }

    cmd->argv[argc] = NULL;
    return cmd;
}

void free_command(Command *cmd) {
    if (!cmd) return;

    if (cmd->argv) {
        for (int i = 0; cmd->argv[i]; i++)
            free(cmd->argv[i]);
        free(cmd->argv);
    }

    if (cmd->pipe_argv) {
        for (int i = 0; cmd->pipe_argv[i]; i++)
            free(cmd->pipe_argv[i]);
        free(cmd->pipe_argv);
    }

    free(cmd->input_file);
    free(cmd->output_file);
    free(cmd);
}

