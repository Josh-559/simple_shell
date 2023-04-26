#include "shell.h"

/**
 * shell_prompt - displays shell prompt to stdout
 */

void shell_prompt(void)
{
	char cwd[PATH_MAX], *formatted_str;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd() error");

	formatted_str = format_tilde(cwd);
	if (formatted_str != NULL)
		_strcpy(cwd, formatted_str);
	print_str(cwd);
	free(formatted_str);
	print_str("$ ");
}
