#include "eshell.h"

/**
 * is_command - determines if a file is an executable command
 * @desc: the desc struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_command(desc_t *desc, char *path)
{
	struct stat path_stat;

	(void)desc;
	if (!path || stat(path, &path_stat))
		return (0);

	if (path_stat.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicate_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @end: ending index
 *
 * Return: pointer to new buffer
 */
char *duplicate_chars(char *pathstr, int start, int end)
{
	static char buff[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < end; i++)
		if (pathstr[i] != ':')
			buff[k++] = pathstr[i];
	buff[k] = 0;
	return (buff);
}

/**
 * command_path - finds this command in the PATH string
 * @desc: the desc struct
 * @pathstr: the PATH string
 * @command: the command to find
 *
 * Return: full path of command if found or NULL
 */
char *command_path(desc_t *desc, char *pathstr, char *command)
{
	int i = 0, current_position = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(command) > 2) && starts_with(command, "./"))
	{
		if (is_command(desc, command))
			return (command);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = duplicate_chars(pathstr, current_position, i);
			if (!*path)
				_strcat(path, command);
			else
			{
				_strcat(path, "/");
				_strcat(path, command);
			}
			if (is_command(desc, path))
				return (path);
			if (!pathstr[i])
				break;
			current_position = i;
		}
		i++;
	}
	return (NULL);
}
