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
	char *cmd;

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
		cmd = get_path(args[0]);
		printf("cmd %s", cmd);

		if (execve(cmd, args, environ) == -1)
		{
			perror(argv0);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
	}
	free(cmd);
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

char *get_path(char *in){
    char *path, *path_cp, *path_token, *file_path;
    int cmd_len, dir_len;
    struct stat buf;

    path = "/bin:/sbin:/tmp";
    if(path)
    {
        path_cp = strdup(path);
        cmd_len = strlen(in);
        path_token = strtok(path_cp, ":");

        while(path_token != NULL){
            dir_len = strlen(path_token);
            file_path = malloc(cmd_len + dir_len + 2);
            strcpy(file_path, path_token);
            strcat(file_path, "/");
            strcat(file_path, in);
            strcat(file_path, "\0");

            if (stat(file_path, &buf) == 0){
                free(path_cp);
                return (file_path);
            }
            else{
                free(file_path);
                path_token = strtok(NULL, ":");

            }
        }
        free(path_cp);

        if (stat(in, &buf) == 0)
        {
            return (in);
        }
        return (NULL);
    }
    return (NULL);
}
