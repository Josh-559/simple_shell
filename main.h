#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <limits.h>
#include <time.h>

/* Define constants */
#define MAX_COMMAND_LENGTH 1024
#define MAX_NUM_ARGUMENTS 10
#define BUFFER_SIZE 1024

/* Declare functions */
void execute_command(char **args);
void parse_command(char *command, char **args);
int _putchar(char c);
char *get_path(char *command, char **envp);
int is_exit_command(char **args);
int is_env_command(char **args);
int print_numbers(int n);
int _strlen(const char *string);
extern char **environ;

#endif /* MAIN_H */