#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>

char *collect_loca(char *execute)

{
	char *path, *path_copy, *path_token, *file_path;
	int execute_len, pathdirect_len;
	struct stat buffer;

	path = getenv("PATH");

	if (path)
	{
		path_copy = strdup(path);
		execute_len = strlen(execute);
		path_token = strtok(path_copy, ":");
		execute_len = strlen(execute);
		path_token = strtok(path_copy, ":");

		while(path_token != NULL)
		{
		pathdirect_len = strlen(path_token);
		file_path = malloc(execute_len + pathdirect_len + 2);
		strcpy(file_path, path_token);
		strcat(file_path, "/");
		strcat(file_path, execute);
		strcat(file_path, "\0");

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

		}
	

		free(path_copy);
	
		if (stat(execute, &buffer) == 0)
		{
			return (execute);
		}

		return (NULL);
	}
	return (NULL);
}
