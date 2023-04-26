#include "shell.h"

/**
 *read_input - function to read user input on the command line
 *@user_input: Command entered by the user
 *
 * Return: Nothing.
 */

void read_input(char *user_input)
{
	ssize_t bytes_read;

	write(STDOUT_FILENO, "$ ", 3);

	bytes_read = read(STDIN_FILENO, user_input, MAX_USER_INPUT_LENGTH);

	if (bytes_read == -1)
	{
		perror("read");
		exit(EXIT_FAILURE);
	}

/* Replace newline character with null terminator */
	user_input[bytes_read - 1] = '\0';
}