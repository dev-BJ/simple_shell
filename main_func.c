#include "main.h"
/**
 * read_input - Read a line of text from standard input.
 *
 * This function reads a line of text from standard input (stdin) and returns
 * it as a dynamically allocated string. It handles end-of-file (Ctrl+D) by
 * returning NULL and freeing the allocated memory.
 *
 * Return: A pointer to the dynamically allocated string containing the input
 *         line, or NULL if end-of-file is reached.
 */
char *read_input(void)
{
	char *input = NULL;
	size_t input_len = 0;

	if (getline(&input, &input_len, stdin) == -1)
	{
		write(STDOUT_FILENO, "\n", 1);
		free(input);
		return (NULL);
	}

	input[_strcspn(input, "\n")] = '\0';
	return (input);
}

/**
 * execute_command - Execute a command using fork and execlp.
 *
 * This function takes a command string and attempts to execute it as a child
 * process using fork and execlp. It waits for the child process to complete
 * before returning in the parent process.
 *
 * @input: The command to execute.
 * @argv0: The name of the calling program for error reporting.
 */
void execute_command(char *input, char *argv0)
{
	if (_strlen(input) > 0)
	{
		pid_t pid = fork();

		if (pid == -1)
		{
			perror(argv0);
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			/* Child process */
			if (execlp(input, input, NULL) == -1)
			{
				perror(argv0);
				exit(EXIT_FAILURE);
			}
			}
		else
		{
			wait(NULL);
		}
	}
}
