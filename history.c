#include "eshell.h"

/**
 * get_history_of_file - gets the history file
 * @desc: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_of_file(desc_t *desc)
{
	char *buff, *dir;

	dir = get_the_env(desc, "HOME=");
	if (!dir)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dir) + _strlen(File_History) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dir);
	_strcat(buff, "/");
	_strcat(buff, File_History);
	return (buff);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @desc: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(desc_t *desc)
{
	ssize_t fd;
	char *filename = get_history_of_file(desc);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = desc->history; node; node = node->next)
	{
		puts_fd(node->str, fd);
		put_fd('\n', fd);
	}
	put_fd(BUFFER_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads history from file
 * @desc: the parameter struct
 *
 * Return: hist_count on success, 0 otherwise
 */
int read_history(desc_t *desc)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buff = NULL, *filename = get_history_of_file(desc);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rdlen = read(fd, buff, fsize);
	buff[fsize] = 0;
	if (rdlen <= 0)
		return (free(buff), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buff[i] == '\n')
		{
			buff[i] = 0;
			build_history_list(desc, buff + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(desc, buff + last, linecount++);
	free(buff);
	desc->hist_count = linecount;
	while (desc->hist_count-- >= HISTORY_MAX)
		delete_node(&(desc->history), 0);
	renumber_history(desc);
	return (desc->hist_count);
}

/**
 * build_history_list - adds entry to a history linked list
 * @desc: Structure containing potential arguments. Used to maintain
 * @buff: bufffer
 * @linecount: the history linecount, hist_count
 *
 * Return: Always 0
 */
int build_history_list(desc_t *desc, char *buff, int linecount)
{
	list_t *node = NULL;

	if (desc->history)
		node = desc->history;
	add_to_node_end(&node, buff, linecount);

	if (!desc->history)
		desc->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @desc: Structure containing potential arguments. Used to maintain
 *
 * Return: the new hist_count
 */
int renumber_history(desc_t *desc)
{
	list_t *node = desc->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (desc->hist_count = i);
}
