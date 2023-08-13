#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

/**
 * main - gets input from user and executes the command
 *
 * @argc: arg count
 * @argv: array list of arg variables
 *
 * Description: run an infinte loop for the custom shell's
 * command prompt. get input from user, strip off the new line character
 * added at the end of user input. check if there's a current running process;
 * if none, execute command otherwise wait for completion then execute command;
 * in case of error, print error statement.
 *
 * Return: success 0, failure -1
 */

int main(__attribute__((unused))int argc, char *argv[])
{
	char *line, *environ[] = {NULL};
	size_t linecap = 0;
	size_t linelen;
	pid_t pid;

	while (1)
	{
		write(STDOUT_FILENO, "#cisfun$ ", 10);
		linelen = getline(&line, &linecap, stdin);
		if ((int)linelen == -1)
		{
			if (feof(stdin))
				break;
			perror("./shell(getline)");
		}
		line[strcspn(line, "\n")] = '\0';
	pid = fork();
	if (pid == 0)
	{
		if (execve(line, argv, environ) == -1)
		{
			perror("./shell(execve)");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	else
		perror("./shell(fork)");
	}

	return (0);
}
