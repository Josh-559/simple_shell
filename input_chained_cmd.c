#include "eshell.h"

/**
 * input_chained_cmd - buffers chained commands
 * @desc: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{

	_puts("\n");
	_puts("$ ");
	_putchar(BUFFER_FLUSH);
}



ssize_t input_chained_cmd(desc_t *desc, char **buf, size_t *len)
{
	ssize_t x = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		x = USE_GETLINE(buf, &len_p, stdin);
#else
		x = _USE_GETLINE(desc, buf, &len_p);
#endif
		if (x > 0)
		{
			if ((*buf)[x - 1] == '\n')
			{
				(*buf)[x - 1] = '\0'; /* remove trailing newline */
				x--;
			}
			desc->count_flag = 1;
			remove_comments(*buf);
			build_history_list(desc, *buf, desc->hist_count++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = x;
				desc->cmd_buff = buf;
			}
		}
	}
	return (x);
}

/**
 * get_input - gets a line minus the newline
 * @desc: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(desc_t *desc)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(desc->arg), *p;

	_putchar(BUFFER_FLUSH);
	r = input_chained_cmd(desc, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)	/* we hargve commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		check_chain(desc, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_chain(desc, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			desc->cmd_buff_type = CMD_NORMAL;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _USE_GETLINE() */
	return (r); /* return length of buffer from _USE_GETLINE() */
}

/**
 * read_buf - reads a buffer
 * @desc: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(desc_t *desc, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(desc->read_fd, buf, READ_BUFFER_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _USE_GETLINE - gets the next line of input from STDIN
 * @desc: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _USE_GETLINE(desc_t *desc, char **ptr, size_t *length)
{
	static char buf[READ_BUFFER_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(desc, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = realloc_memory(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

