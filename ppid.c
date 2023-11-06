#include <stdio.h>
#include <unistd.h>

/**
*main - This program prints PPID of the parents process
*
*Return: 0.
*/

int main(void)
{
	pid_t my_ppid;

	my_ppid = getpid();
	printf("Parent Process ID (PPID) %u\n", my_ppid);
	return (0);
}
