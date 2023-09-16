#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_INPUT_LEN 1024

#define UNUSED(x) (void)(x)

/* strings */
size_t _strlen(const char *str);
size_t _strcspn(const char *s1, const char *s2);

/* shell functions */
int main(int argc, char *argv[]);
void print_prompt(void);
void execute_command(char *input, char *argv0);
char *read_input(void);

#endif
