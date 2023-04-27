#include "eshell.h"

/**
 * clear_desc - initializes desc_t struct
 * @desc: struct address
 */
void clear_desc(desc_t *desc)
{
	desc->arg = NULL;
	desc->argv = NULL;
	desc->path = NULL;
	desc->argc = 0;
}

/**
 * set_desc - initializes desc_t struct
 * @desc: struct address
 * @argv: argument vector
 */
void set_desc(desc_t *desc, char **argv)
{
	int i = 0;

	desc->fname = argv[0];
	if (desc->arg)
	{
		desc->argv = strtokenizer(desc->arg, " \t");
		if (!desc->argv)
		{

			desc->argv = malloc(sizeof(char *) * 2);
			if (desc->argv)
			{
				desc->argv[0] = _strdup(desc->arg);
				desc->argv[1] = NULL;
			}
		}
		for (i = 0; desc->argv && desc->argv[i]; i++)
			;
		desc->argc = i;

		replace_alias(desc);
		replace_vars(desc);
	}
}

/**
 * free_desc - frees desc_t struct fields
 * @desc: struct address
 * @all: true if freeing all fields
 */
void free_desc(desc_t *desc, int all)
{
	ffree(desc->argv);
	desc->argv = NULL;
	desc->path = NULL;
	if (all)
	{
		if (!desc->cmd_buff)
			free(desc->arg);
		if (desc->env)
			free_node(&(desc->env));
		if (desc->history)
			free_node(&(desc->history));
		if (desc->alias)
			free_node(&(desc->alias));
		ffree(desc->environ);
			desc->environ = NULL;
		free_pointer((void **)desc->cmd_buff);
		if (desc->read_fd > 2)
			close(desc->read_fd);
		_putchar(BUFFER_FLUSH);
	}
}
