#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

/**
 * print_error - prints error message
 */

void print_error(void)
{
	perror("./shell");
}

/**
 * print_prompt - display's user command prompt
 */

void print_prompt(void)
{
	write(STDOUT_FILENO, "#cisfun$ ", 10);
}

/**
 * handle_args - tokenizes command line arguments and
 * sets them in argv
 *
 * @iptr: pointer to user input
 * @argv: list of argument variables
 *
 * Return: int
 */

int handle_args(char **iptr, char **argv)
{
	char *token;
	int i = 0;

	token = strtok(*iptr, " ");
	while (token != NULL)
	{
		argv[i] = token;
		i++;
		printf("%s\n", token);
		token = strtok(NULL, " ");
	}
	argv[i] = NULL;
	return (0);
}

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

int main(__attribute__((unused))int argc, char *argv[], __attribute__((unused))char *envp[])
{
	char *line = {NULL};
	size_t size = 0;
	ssize_t linelen;
	pid_t pid;
	int status;

	while (1)
	{
		print_prompt();
		linelen = getline(&line, &size, stdin);
		if (linelen == -1)
		{
			if (feof(stdin))
				break;
			print_error();
		}
		line[strlen(line) - 1] = '\0';
	pid = fork();
	if (pid == 0)
	{
		handle_args(&line, argv);
		if (execve(argv[0], argv, envp) == -1)
		{
			print_error();
			free(line);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		print_error();
	}

	free(line);
	return (0);
}
