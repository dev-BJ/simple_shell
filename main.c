#include "main.h"

/**
 * print_prompt - Prints the shell prompt.
 */
void print_prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		char prompt[] = "$ ";

		write(STDOUT_FILENO, prompt, strlen(prompt));
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
	char *input = NULL;

	UNUSED(argc);

	while (1)
	{
		print_prompt();
		input = read_input();

		if (input == NULL)
		{
			break;
		}
		handle_exit(input);
		print_env(input);
		/*printf("find path for %s = %s \n",input,get_path(input));*/

		execute_command(input, argv[0]);
		free(input);
	}
	return (EXIT_SUCCESS);
}
