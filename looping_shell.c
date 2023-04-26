#include "eshell.h"

/**
 * main_hsh - main shell loop
 * @desc: the parameter & return desc struct
 * @argv: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int main_hsh(desc_t *desc, char **argv)
{
	ssize_t x = 0;
	int builtin_returned = 0;

	while (x != -1 && builtin_returned != -2)
	{
		clear_desc(desc);
		if (interactive(desc))
			_puts("$ ");
		_errorchar(BUFFER_FLUSH);
		x = get_input(desc);
		if (x != -1)
		{
			set_desc(desc, argv);
			builtin_returned = builtin_command(desc);
			if (builtin_returned == -1)
				find_command(desc);
		}
		else if (interactive(desc))
			_putchar('\n');
		free_desc(desc, 0);
	}
	write_history(desc);
	free_desc(desc, 1);
	if (!interactive(desc) && desc->status)
		exit(desc->status);
	if (builtin_returned == -2)
	{
		if (desc->error_num == -1)
			exit(desc->status);
		exit(desc->error_num);
	}
	return (builtin_returned);
}

/**
 * builtin_command - finds a builtin command
 * @desc: the parameter & return desc struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int builtin_command(desc_t *desc)
{
	int i, builtin_returned = -1;
	builtin_t builtintbl[] = {
		{"exit", fx_exit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"__setenv", _my__setenv},
		{"un__setenv", _myun__setenv},
		{"cd", change_dir},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(desc->argv[0], builtintbl[i].type) == 0)
		{
			desc->line_count++;
			builtin_returned = builtintbl[i].func(desc);
			break;
		}
	return (builtin_returned);
}

/**
 * find_command - finds a command in PATH
 * @desc: the parameter & return desc struct
 *
 * Return: void
 */
void find_command(desc_t *desc)
{
	char *path = NULL;
	int i, j;

	desc->path = desc->argv[0];
	if (desc->count_flag == 1)
	{
		desc->line_count++;
		desc->count_flag = 0;
	}
	for (i = 0, j = 0; desc->arg[i]; i++)
		if (!is_delim(desc->arg[i], " \t\n"))
			j++;
	if (!j)
		return;

	path = command_path(desc, get_the_env(desc, "PATH="), desc->argv[0]);
	if (path)
	{
		desc->path = path;
		fork_the_command(desc);
	}
	else
	{
		if ((interactive(desc) || get_the_env(desc, "PATH=")
			|| desc->argv[0][0] == '/') && is_command(desc, desc->argv[0]))
			fork_the_command(desc);
		else if (*(desc->arg) != '\n')
		{
			desc->status = 127;
			print_the_error(desc, "not found\n");
		}
	}
}

/**
 * fork_the_command - forks a an exec thread to run commands
 * @desc: the parameter & return desc struct
 *
 * Return: void
 */
void fork_the_command(desc_t *desc)
{
	pid_t pid1;

	pid1 = fork();
	if (pid1 == -1)
	{
		/* PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (pid1 == 0)
	{
		if (execve(desc->path, desc->argv, get_the_environ(desc)) == -1)
		{
			free_desc(desc, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(desc->status));
		if (WIFEXITED(desc->status))
		{
			desc->status = WEXITSTATUS(desc->status);
			if (desc->status == 126)
				print_the_error(desc, "Permission has been denied\n");
		}
	}
}
