#include "eshell.h"

/**
 **memory_set - fills memory with a constant byte
 *@holder_ptr: the pointer to the memory area
 *@byte: the byte to fill *holder_ptr with
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *memory_set(char *holder_ptr, char byte, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		holder_ptr[i] = byte;
	return (holder_ptr);
}

/**
 * ffree - frees a string of strings
 * @dp: string of strings
 */
void ffree(char **dp)
{
	char **a = dp;

	if (!dp)
		return;
	while (*dp)
		free(*dp++);
	free(a);
}

/**
 * realloc_memory - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @prev_size: byte size of previous block
 * @upd_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *realloc_memory(void *ptr, unsigned int prev_size, unsigned int upd_size)
{
	char *p;

	if (!ptr)
		return (malloc(upd_size));
	if (!upd_size)
		return (free(ptr), NULL);
	if (upd_size == prev_size)
		return (ptr);

	p = malloc(upd_size);
	if (!p)
		return (NULL);

	prev_size = prev_size < upd_size ? prev_size : upd_size;
	while (prev_size--)
		p[prev_size] = ((char *)ptr)[prev_size];
	free(ptr);
	return (p);
}
