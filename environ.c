#include "eshell.h"

/**
 * _myenv - prints the current environment
 * @desc: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(desc_t *desc)
{
	display_list_str(desc->env);
	return (0);
}

/**
 * get_the_env - gets the value of an environ variable
 * @desc: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *get_the_env(desc_t *desc, const char *name)
{
	list_t *node = desc->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _my__setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @desc: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _my__setenv(desc_t *desc)
{
	if (desc->argc != 3)
	{
		input_e("Incorrect number of arguements\n");
		return (1);
	}
	if (__setenv(desc, desc->argv[1], desc->argv[2]))
		return (0);
	return (1);
}

/**
 * _myun__setenv - Remove an environment variable
 * @desc: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myun__setenv(desc_t *desc)
{
	int i;

	if (desc->argc == 1)
	{
		input_e("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= desc->argc; i++)
		_un__setenv(desc, desc->argv[i]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @desc: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(desc_t *desc)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_to_node_end(&node, environ[i], 0);
	desc->env = node;
	return (0);
}
