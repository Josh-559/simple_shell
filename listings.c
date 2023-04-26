#include "eshell.h"

/**
 * legth_list - determines length of linked list
 * @first_node: pointer to first node
 *
 * Return: size of list
 */
size_t legth_list(const list_t *first_node)
{
	size_t i = 0;

	while (first_node)
	{
		first_node = first_node->next;
		i++;
	}
	return (i);
}

/**
 * returned_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */

char **returned_strings(list_t *head)
{
	list_t *node = head;
	size_t i = legth_list(head), j;
	char **lists;
	char *str;

	if (!head || !i)
		return (NULL);
	lists = malloc(sizeof(char *) * (i + 1));
	if (!lists)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(lists[j]);
			free(lists);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		lists[i] = str;
	}
	lists[i] = NULL;
	return (lists);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @first_node: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *first_node)
{
	size_t i = 0;

	while (first_node)
	{
		_puts(convert_number(first_node->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(first_node->str ? first_node->str : "(nil)");
		_puts("\n");
		first_node = first_node->next;
		i++;
	}
	return (i);
}

/**
 * first_node_starts_with - returns node whose string starts with prefix
 * @head: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *first_node_starts_with(list_t *head, char *prefix, char c)
{
	char *p = NULL;

	while (head)
	{
		p = starts_with(head->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (head);
		head = head->next;
	}
	return (NULL);
}

/**
 * findd_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t findd_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
