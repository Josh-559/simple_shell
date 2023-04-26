#include "shell.h"

/**
*builtin_exit - exits the shell program
*
* Return: Nothing
*/
int builtin_exit(void)
{
	exit(EXIT_SUCCESS);
}

/**
*builtin_env - prints the environment variables
*
* Return: 0 on success
*
*/

int builtin_env(void)
{
	char *env_var;

	while ((env_var = *environ++) != NULL)
	{
		write(STDOUT_FILENO, env_var, strlen(env_var));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}

/**
*builtin_cd - changes the directory
*@user_input: the command entered by the user
*
* Return: 0 on Success; -1 if failed
*/
int builtin_cd(char *user_input)
{
	char *path;

	path = strchr(user_input, ' ');
	if (path == NULL)
	{
		if (chdir(getenv("HOME")) != 0)
		{
			perror("chdir");
			return (-1);
		}
	}
	else
	{
		++path;
		if (chdir(path) != 0)
		{
			perror("chdir");
			return (-1);
		}
	}
	return (0);
}

/**
 * handle_builtin - handles the builtin commands
 * @user_input: the command inputted
 *
 * Return: (Success) Pointer to the corresponding builtin function
 * ------- (Failure) -1
*/
int handle_builtin(char *user_input)
{
	int i;
	const char * const builtins[] = {"exit", "env", NULL};

	int (* const builtin_funcs[])(void) = {&builtin_exit, &builtin_env, NULL};

	for (i = 0; builtins[i] != NULL; ++i)
	{
		if (strcmp(user_input, builtins[i]) == 0)
		{
			return ((*builtin_funcs[i])());
		}
	}
	return (-1);
}

/**
*is_built_in_command - checks if the user_input is a built_in command
*@user_input: the command entered by user
* Return: 1 on success, 0 if failed
*/

int is_built_in_command(char *user_input)
{
	int num_built_in_commands;
	int i;
	const char * const builtins[3] = {"exit", "env", NULL};

	num_built_in_commands = 3;
	for (i = 0; i < num_built_in_commands - 1; i++)
	{
		if (strcmp(user_input, builtins[i]) == 0)
		{
			return (1);
		}
	}
	return (0);
}