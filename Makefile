CC = gcc
CFLAGS = -Wall -Wextra -g
INC = -Iinclude

SRC = src/main.c src/parse.c src/execute.c src/builtin.c src/signals.c src/logger.c
OBJ = $(SRC:.c=.o)

myshell: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o myshell

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJ) myshell

