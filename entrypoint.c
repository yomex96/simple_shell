#include "simple_shell.h"
char *name;
/**
 * main - print prompt, handle EOF, read file_stream
 * @argc: arg count (not needed)
 * @argv: argv for command
 * Return: Always 0.
 */

int main(int argc, char *argv[])
{
	char *str = NULL;
	size_t buff_size = 0;
	ssize_t fs = 0;

	(void) argc;
	name = argv[0];

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
			write(1, "$ ", 2);
		fs = getline(&str, &buff_size, stdin);
		if (fs == -1)
		{
			if (isatty(STDIN_FILENO) == 1)
				write(1, "\n", 1);
			break;
		}

		if (str[fs - 1]  == '\n')
			str[fs - 1]  = '\0';
		if (*str == '\0')
			continue;
		if (readcmd(str, fs) == 2)
			break;
	}
	free(str);
	str = NULL;
	return (0);
}
/**
 * readcmd - handles command line and tokenizes it
 *@s: string
 *@file_stream: getline input
 * Return: 0
 */
int readcmd(char *s, size_t __attribute__((unused))file_stream)
{
	char *tkn = NULL;
	char *command_array[100];
	int ab;

	if (__mystrcmp(s, "exit") == 0)
		return (2);
	else if (__mystrcmp(s, "env") == 0)
		return (__printenv());
	else if (__mystrncmp(s, "setenv", 6) == 0)
	{
		char *variable, *value;

		variable = strtok(s + 7, " ");
		value = strtok(NULL, " ");
		if (variable != NULL && value != NULL)
			return (mysetenv(variable, value, 1));
		{
			fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
			return (-1);
		}
	}
	else if (__mystrncmp(s, "unsetenv", 8) == 0)
	{
		char *variable = strtok(s + 9, " ");

		if (variable != NULL)
			return (myunsetenv(variable));
		{
			fprintf(stderr, "Usage: unsetenv VARIABLE\n");
			return (-1);
		}
	}
	tkn = strtok(s, " "), ab = 0;
	while (tkn)
	{
		command_array[ab++] = tkn;
		tkn = strtok(NULL, " ");
	}
	command_array[ab] = NULL;
	return (call_command(command_array));
}
/**
 * print_not_found - prints when cmd is not found in path
 *
 * @cmd: a string provided by the stdin
 */
void print_not_found(char *cmd)
{
	write(2, name, __mystrlen(name));
	write(2, ": 1: ", 5);
	write(2, cmd, __mystrlen(cmd));
	write(2, ": not found\n", 12);
}
/**
 * call_command - calls cmd, forks, execve
 *
 * @cmd_arr: a string provided by the stdin
 * Return: 0
 */
int call_command(char *cmd_arr[])
{
	char *execute_path_string = NULL;
	char *command = NULL;
	pid_t is_child;
	int stat;

	command = cmd_arr[0];
	execute_path_string = __mygetpath(command);
	if (execute_path_string == NULL)
	{
		print_not_found(command);
		return (3);
	}
	is_child = fork();
	if (is_child < 0)
	{
		perror("Error:");
		return (-1);
	}
	if (is_child > 0)
		wait(&stat);
	else if (is_child == 0)
	{
		(execve(execute_path_string, cmd_arr, environ));
		perror("Error:");
		exit(1);
	}
	free(execute_path_string);
	return (0);
}


