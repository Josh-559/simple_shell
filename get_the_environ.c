#include "eshell.h"

/**
 * get_the_environ - returns the string array copy of our environ
 * @desc: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_the_environ(desc_t *desc)
{
	if (!desc->environ || desc->env_changed)
	{
		desc->environ = returned_strings(desc->env);
		desc->env_changed = 0;
	}

	return (desc->environ);
}

/**
 * _un__setenv - Remove an environment variable
 * @desc: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _un__setenv(desc_t *desc, char *var)
{
	list_t *node = desc->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			desc->env_changed = delete_node(&(desc->env), i);
			i = 0;
			node = desc->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (desc->env_changed);
}

/**
 * __setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @desc: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int __setenv(desc_t *desc, char *var, char *value)
{
	char *buff = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buff = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, var);
	_strcat(buff, "=");
	_strcat(buff, value);
	node = desc->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buff;
			desc->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_to_node_end(&(desc->env), buff, 0);
	free(buff);
	desc->env_changed = 1;
	return (0);
}
