#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "builtin.h"

int handle_builtin(char **argv) {
    if (!argv || !argv[0]) return 0;

    if (strcmp(argv[0], "exit") == 0 || strcmp(argv[0], "quit") == 0)
        return 2;

    if (strcmp(argv[0], "cd") == 0) {
        char *path = argv[1] ? argv[1] : getenv("HOME");
        if (chdir(path) != 0) perror("cd");
        return 1;
    }

    return 0;
}

