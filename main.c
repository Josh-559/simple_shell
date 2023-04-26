#include "eshell.h"

/**
 * main - entry point
 * @ac: arg count
 * @argv: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	desc_t desc[] = { desc_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				input_e(argv[0]);
				input_e(": 0: Can't open ");
				input_e(argv[1]);
				_errorchar('\n');
				_errorchar(BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		desc->read_fd = fd;
	}
	populate_env_list(desc);
	read_history(desc);
	main_hsh(desc, argv);
	return (EXIT_SUCCESS);
}
