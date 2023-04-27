#include "eshell.h"

/**
 * fx_exit - exits the shell
 * @desc: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if desc.argv[0] != "exit"
 */
int fx_exit(desc_t *desc)
{
	int exitcheck;

	if (desc->argv[1])  /* If there is an exit arguement */
	{
		exitcheck = _string_to_int(desc->argv[1]);
		if (exitcheck == -1)
		{
			desc->status = 2;
			print_the_error(desc, "Illegal number: ");
			input_e(desc->argv[1]);
			_errorchar('\n');
			return (1);
		}
		desc->error_num = _string_to_int(desc->argv[1]);
		return (-2);
	}
	desc->error_num = -1;
	return (-2);
}

/**
 * change_dir - changes the current directory of the process
 * @desc: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int change_dir(desc_t *desc)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!desc->argv[1])
	{
		dir = get_the_env(desc, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = get_the_env(desc, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(desc->argv[1], "-") == 0)
	{
		if (!get_the_env(desc, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(get_the_env(desc, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = get_the_env(desc, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(desc->argv[1]);
	if (chdir_ret == -1)
	{
		print_the_error(desc, "can't cd to ");
		input_e(desc->argv[1]), _errorchar('\n');
	}
	else
	{
		__setenv(desc, "OLDPWD", get_the_env(desc, "PWD="));
		__setenv(desc, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the current directory of the process
 * @desc: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myhelp(desc_t *desc)
{
	char **arg_array;

	arg_array = desc->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
