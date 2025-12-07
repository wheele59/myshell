# myshell – Mini Unix Shell
Author: Alex Wheeler (wheele59)  
Course: 12600
Semester: Fall 2025  

Overview

myshell is a simplified Unix command-line shell written in C. It supports execution of external programs, background jobs, pipes, I/O redirection, signal handling, and command logging. The project was created to practice process control, dynamic memory management, and system-level programming using POSIX system calls.

This shell intentionally does not fully replicate Bash and only implements the features required by the project specification.

Features Implemented

External Commands
- Executes programs using fork() and execvp()
- Supports command arguments

Built-in Commands
- exit or quit terminates the shell
- cd [path] changes directory
- If no path is provided, cd changes to the HOME directory
- Built-ins execute in the parent process

I/O Redirection
- > redirects stdout (truncate)
- >> redirects stdout (append)
- < redirects stdin

Pipes
- Supports exactly one pipe: cmd1 | cmd2

Background Jobs
- Commands ending with & run in the background
- The shell does not block
- Prints: [bg] started pid <pid>

Signal Handling
- Shell ignores SIGINT
- Child processes restore default SIGINT behavior
- SIGCHLD handler prevents zombie processes

Command Logging
- All external commands are logged to myshell.log
- Logging uses open(), snprintf(), and write()
- Logged fields include PID, raw command, and exit status

Memory Management
- Dynamic memory with malloc()
- All memory freed each loop
- Valgrind verified clean with no memory leaks or errors

Multi-file Project Structure

src/
  main.c
  parse.c
  execute.c
  builtin.c
  signals.c
  logger.c

include/
  parse.h
  execute.h
  builtin.h
  signals.h
  logger.h

Makefile

The Makefile supports:
- make
- make clean

Compilation uses:
- -Wall
- -Wextra
- -g

Executable name:
- myshell

Build Instructions

Run:
make

This will produce the executable myshell.

To clean build files:
make clean

Run Instructions

Start the shell with:
./myshell

Exit using:
exit
or
quit

Sample Commands

ls
ls -l
grep main src/*.c
ls > out.txt
cat < out.txt
ls | wc
sleep 3 &
cd /tmp
exit

Known Limitations

- Only one pipe is supported
- No quoting support
- No environment variable expansion
- No scripting or job control beyond background execution
- No command history
