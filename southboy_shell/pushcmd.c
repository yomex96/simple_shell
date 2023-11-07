#include "main.h"

void pushcmd(char **argv)
{
	char *execute = NULL, *exact_execute = NULL;

	if (argv) 
	{
	execute = argv[0];
	exact_execute = collect_loca(execute);

	if (execve(exact_execute, argv, NULL) == -1)
	{
		perror("Error executing command:");
		exit(EXIT_FAILURE);
	}

	free(exact_execute); /* Clean up allocated memory */
	}
}
