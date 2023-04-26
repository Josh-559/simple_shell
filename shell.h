#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

/* defining macros */
#define MAX_USER_INPUT_LENGTH 1024
#define MAX_ARGUMENTS 10
#define MAX_ERROR_LENGTH 256


/* global environment variable */
extern char **environ;

/* functions declaration */

void read_input(char *user_input);
void execute_input(char *user_input);
void set_path(void);
char *find_command(char *user_input);
void execute_command_without_args(char *user_input);
void execute_command_with_args(char *user_input);
int is_built_in_command(char *user_input);
int handle_builtin(char *user_input);
int builtin_cd(char *user_input);
int builtin_env(void);
int builtin_exit(void);
char *_strdup(char *str);
char *_strcpy(char *dest, char *source);
char *_strchr(char *str, char c);
int _strcmp(const char *s1, const char *s2);
int _strlen(char *str);
char *_strcat(char *dest, const char *src);
void handle_signal(int identifier);

#endif