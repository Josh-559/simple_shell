#include "eshell.h"

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @desc: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory(desc_t *desc)
{
	print_list(desc->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @desc: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(desc_t *desc, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node(&(desc->alias),
		findd_node_index(desc->alias, first_node_starts_with(desc->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @desc: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(desc_t *desc, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(desc, str));

	unset_alias(desc, str);
	return (add_to_node_end(&(desc->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @desc: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(desc_t *desc)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (desc->argc == 1)
	{
		node = desc->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; desc->argv[i]; i++)
	{
		p = _strchr(desc->argv[i], '=');
		if (p)
			set_alias(desc, desc->argv[i]);
		else
			print_alias(first_node_starts_with(desc->alias, desc->argv[i], '='));
	}

	return (0);
}
