#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "main.h"

void pushcmd(char **argv);

int main(int ac, char **argv)
{
	char *prompt = "(south) $ ";
	char *lineptr = NULL, *lineptr_copy = NULL;
	size_t n = 0;
	ssize_t hd_retval;
	const char *delim = " \n";
	char *token;
	int number_toks = 0;
	int i;

	(void)ac; /** declaring void variables **/

	for (;;)
	{
	printf("%s", prompt);

	hd_retval = getline(&lineptr, &n, stdin);

	if (hd_retval == -1) /** checks if getline func fails **/
	{
		printf("Quitting shell...\n");
		free(lineptr); /** free allocated memory **/
		return (-1);
	}

	lineptr_copy = malloc(sizeof(char) * hd_retval);
	if (lineptr_copy == NULL)
	{
		perror("tsh: memory allocation error");
		free(lineptr); /** free allocated memory **/
		return (-1);
	}

	strcpy(lineptr_copy, lineptr);

	token = strtok(lineptr, delim);

	for (number_toks = 0; token != NULL; number_toks++)
	{
		token = strtok(NULL, delim);
	}
		number_toks++;

	argv = malloc(sizeof(char *) * number_toks);

	token = strtok(lineptr_copy, delim);

	for (i = 0; token != NULL; i++)
	{
		argv[i] = malloc(sizeof(char) * strlen(token));
		strcpy(argv[i], token);
		token = strtok(NULL, delim);
	}
		argv[i] = NULL;
		pushcmd(argv);

		free(lineptr_copy); /** free allocated memory **/
		free(lineptr);
	}

	return (0);
}
