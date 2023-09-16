#include "main.h"

/**
 * print_prompt - Prints the shell prompt.
 */
void print_prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		char prompt[] = "$ ";

		write(STDOUT_FILENO, prompt, _strlen(prompt));
		fflush(stdout);
	}
}

/**
 * main- entry point for the simple shell program
 * @argc: argument count..
 * @argv: commandline arguments.
 *
 * Return: 0
 */
int main(int argc, char *argv[])
{
	UNUSED(argc);

	while (1)
	{
		char *input;

		print_prompt();
		input = read_input();

		if (input == NULL)
		{
			break;
		}
		execute_command(input, argv[0]);
		free(input);
	}
	return (EXIT_SUCCESS);
}
