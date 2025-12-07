#ifndef PARSE_H
#define PARSE_H

typedef struct {
    char **argv;
    char *input_file;
    char *output_file;
    int append;
    int background;
    char **pipe_argv;
} Command;

Command *parse_line(char *line);
void free_command(Command *cmd);

#endif

