#include "simple_shell.h"

/**
 * __mygetpath - accepts PATH string, splits it to tokens, then concats
 * with "/" & cmd
 *@command: command passed from getline in main
 *
 * Return: new_path for use in cmd_read
 */
char *__mygetpath(char *command)
{
	char *path = __mystrdup(__mygetenv("PATH"));
	int ab = 0, xy = 0;
	char *path_tokens = strtok(path, ":");
	char *path_array[100];
	char *s2 = command;
	char *new_path = NULL;
	struct stat buf;

	new_path = malloc(sizeof(char) * 100);
	if (__mygetenv("PATH")[0] == ':')
		if (stat(command, &buf) == 0)
			return (__mystrdup(command));
	while (path_tokens != NULL)
	{
		path_array[ab++] = path_tokens;
		path_tokens = strtok(NULL, ":");
	}
	path_array[ab] = NULL;
	for (xy = 0; path_array[xy]; xy++)
	{
		__mystrcpy(new_path, path_array[xy]);
		__mystrcat(new_path, "/");
		__mystrcat(new_path, s2);
		__mystrcat(new_path, "\0");

		if (stat(new_path, &buf) == 0)
		{
			free(path);
			return (new_path);
		}
		else
			new_path[0] = 0;
	}
	free(path);
	free(new_path);

/* This is for after PATH checked and cmd is there locally */
	if (stat(command, &buf) == 0)
		return (__mystrdup(command));
	return (NULL);
}
/**
 * mysetenv - Initialize a new environment variable or modify an existing one
 * @variable: Name of the environment variable
 * @value: Value to set for the environment variable
 * @overwrite: If set to 1, overwrite the existing value; if 0,
 * do nothing if the variable exists
 *
 * Return: 0 on success, -1 on failure
 */
int mysetenv(char *variable, char *value, int overwrite)
{
	if (variable == NULL || value == NULL)
	{
		fprintf(stderr, "setenv: Invalid arguments\n");
		return (-1);
	}

    /* Check if the variable already exists */
	char *existing_value = __mygetenv(variable);

	if (existing_value != NULL && overwrite == 0)
	{
		fprintf(stderr, "setenv: Variable '%s' already exists\n", variable);
		return -1;
	}

    /* Allocate memory for the new environment variable*/
    char *new_variable = malloc(__mystrlen(variable) + __mystrlen(value) + 2);
	/* +2 for '=' and '\0'*/

    if (new_variable == NULL) {
        perror("setenv");
        return -1;
    }

    /* Concatenate the variable name, '=', and value*/
    __mystrcpy(new_variable, variable);
    __mystrcat(new_variable, "=");
    __mystrcat(new_variable, value);

    /* Set the new environment variable*/
    if (putenv(new_variable) != 0) {
        perror("setenv");
        free(new_variable);
        return -1;
    }

    return 0;
}

/**
 * myunsetenv - Remove an environment variable
 * @variable: Name of the environment variable to remove
 *
 * Return: 0 on success, -1 on failure
 */
int myunsetenv(char *variable) {
    if (variable == NULL) {
        fprintf(stderr, "unsetenv: Invalid argument\n");
        return -1;
    }

    /* Use unsetenv to remove the environment variable */
    if (unsetenv(variable) != 0) {
        perror("unsetenv");
        return -1;
    }

    return 0;
}
