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
		/*write(STDOUT_FILENO, "\n", 1);*/
		free(input);
		return (NULL);
	}

	input[strcspn(input, "\n")] = '\0';
	return (input);
}

/**
 * execute_command - Execute a command using fork and execlp.
 *
 * @input: The command to execute.
 * @argv0: The name of the calling program for error reporting.
 */
void execute_command(char *input, char *argv0)
{
	char *trimmed_input = input + strspn(input, " ");
	size_t input_length = strlen(trimmed_input);
	pid_t pid = fork();

	if (input_length == 0)
	{
		return;
	}
	if (pid == -1)
	{
		perror(argv0);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		char *args[MAX_INPUT_LENGTH];
		int arg_count = 0;
		char *token = strtok(trimmed_input, " ");

		while (token != NULL)
		{
			args[arg_count++] = token;
			token = strtok(NULL, " ");
		}
		args[arg_count] = NULL;

		if (execve(args[0], args, environ) == -1)
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

/**
 * handle_exit - Handles the "exit" command.
 *
 * @input: The input string to check.
 */
void handle_exit(char *input)
{
	if (strcmp(input, "exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}
}

/**
 * print_env - Handles the "env" by printing the
 * the current environment
 *
 * @input: The input string to check.
 */
void print_env(char *input)
{
	if (strcmp(input, "env") == 0)
	{
		char **env = environ;

		while (*env)
		{
			size_t len = strlen(*env);

			write(STDOUT_FILENO, *env, len);
			write(STDOUT_FILENO, "\n", 1);
			env++;
		}
	}
}
