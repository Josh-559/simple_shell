#include "shell.h"

/**
 * main - Simple Shell Command Prompt
 *
 * Return: Always 0.
 */
int main(void)
{
        char *command;
        char buffer[BUFFER_SIZE];
        char *args[] = {buffer, NULL};
        pid_t child_pid;
        int status;

        while (1)
        {
                printf("#cisfun$ ");
                fflush(stdout);

                if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
                        break;

                buffer[strcspn(buffer, "\n")] = '\0';

                child_pid = fork();

                if (child_pid == -1)
                {
                        fprintf(stderr, "%s: ", command);
                        perror("");
                        exit(1);
                }

                if (child_pid == 0)
                {
                        if (execve(args[0], args, NULL) == -1)
                        {
                                fprintf(stderr, "%s: ", command);
                                perror("");
                                exit(1);
                        }
                }
                else
                {
                        waitpid(child_pid, &status, 0);
                }
        }

        return (0);
}
