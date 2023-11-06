#include <stdio.h>

/* The function prints arguments without using argc */

int main(int argc, char *argv[])
{
	int i;
	(void) argc;

	while (argv[i] != NULL)
	{
		printf("%s\n", argv[i]);
		i++;
	}
	return (0);
}
