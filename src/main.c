#include <stdio.h>
#include <string.h>
#include "parse.h"
#include "execute.h"
#include "builtin.h"
#include "signals.h"
#include "logger.h"

int main(void) {
    setup_signals();
    logger_init();

    char line[1024];

    while (1) {
        printf("myshell> ");
        fflush(stdout);

        if (!fgets(line, sizeof(line), stdin))
            break;

        int only_ws = 1;
        for (int i = 0; line[i] != '\0'; i++) {
            if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n') {
                only_ws = 0;
                break;
            }
        }
        if (only_ws)
            continue;

        char raw_line[1024];
        strncpy(raw_line, line, sizeof(raw_line) - 1);
        raw_line[sizeof(raw_line) - 1] = '\0';

        Command *cmd = parse_line(line);
        if (!cmd || !cmd->argv || !cmd->argv[0]) {
            free_command(cmd);
            continue;
        }

        int result = handle_builtin(cmd->argv);
        if (result == 2) {
            free_command(cmd);
            break;
        } else if (result == 1) {
            free_command(cmd);
            continue;
        }

        execute_command(cmd, raw_line);
        free_command(cmd);
    }

    return 0;
}

