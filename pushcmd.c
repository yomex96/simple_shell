#include "main.h"

void pushcmd(char **argv)
{
	char *execute = NULL, *exact_execute = NULL;

	if (argv)
	{
		execute = argv[0]; /** This execute command **/
		exact_execute = collect_loca(execute);

		if (execve(exact_execute, argv, NULL) == -1)
		{
			perror("Error:");
		};
	}
}
