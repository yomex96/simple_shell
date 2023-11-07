#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>

char *collect_loca(char *execute)
{
	char *path = getenv("PATH");
	char *path_copy, *path_token, *file_path = NULL;
	int execute_len, pathdirect_len;
	struct stat buffer;

	if (!path)
	{
	return (NULL);
	}

	path_copy = strdup(path);
	if (!path_copy)
	{
	perror("Error: Memory allocation failed");
	return (NULL);
	}

	execute_len = strlen(execute);
	path_token = strtok(path_copy, ":");

	while (path_token != NULL)
	{
		pathdirect_len = strlen(path_token);
		file_path = malloc(execute_len + pathdirect_len + 1);

		if (!file_path)
		{
		perror("Error: Memory allocation failed");
		free(path_copy);
		return (NULL);
		}

		strcpy(file_path, path_token);
		strcat(file_path, "/");
		strcat(file_path, execute);

		if (stat(file_path, &buffer) == 0)
		{
		free(path_copy);
		return (file_path);
		}	
		else
		{
		free(file_path);
		path_token = strtok(NULL, ":");
		}
		if (stat(execute, &buffer) == 0)
		{
			return (execute);
		}
	}
	return (NULL);
}
