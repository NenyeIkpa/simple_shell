#include <stdio.h>
#include <unistd.h>

/**
 * main - prints process id and parent's process id
 * pid_t: data type for process ids. it is a signed integer
 *
 * Return: int
 */
int main(void)
{
	pid_t process_id, parent_pid;

	process_id = getpid();
	parent_pid = getppid();

	printf("%d\n", process_id);
	printf("%d\n", parent_pid);

	return (0);
}
