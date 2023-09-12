#include "main.h"
/**
 * main- entry point for the simple shell program
 * @argc: argument count..
 * @argv: commandline arguments.
 *
 * Return: 0
 */
int main(int argc, char **argv)
{
	size_t in_count = 0;
	ssize_t gl_res;
	char *line_in;
	int exe_res;
	char *arg[2] = {NULL, NULL};
	char *env[] = {NULL};

	(void)argc;
	printf("%s\n", argv[0]);

	while(1)
	{
		printf("($) ");
		gl_res = getline(&line_in, &in_count, stdin);
		if(gl_res == -1)
			return -1;
		/*printf("%s\n", line_in);*/
		arg[0] = malloc(sizeof(char) * 10);
		strcpy(arg[0], line_in);
		exe_res = execve(arg[0], arg, env);
		if(exe_res == -1)
		{
			printf("%s : %s\n", argv[0], "No such file or directory");
		}
		
		/*free(line_in);*/
	}
	free(arg);
	free(line_in);
	return 0;
}
