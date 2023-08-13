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
 * execute_cmd - executes command parsed to the prompt
 *
 * @cmd: command to be executed
 * @argv: list of argument variables
 * @envp: list of environment variables
 */

void execute_cmd(char *cmd, char **argv, char **envp)
{
	if (fork() == 0)
	{
		if (execve(cmd, argv, envp) == -1)
		{
			print_error();
			free(cmd);
			exit(EXIT_FAILURE);
		}
	}
	else if (fork() > 0)
		wait(NULL);
}


/**
 * get_input - gets input from user
 *
 * Return: user input
 */

char *get_input(void)
{
	char *input;
	size_t len = 0;
	ssize_t result;

	result = getline(&input, &len, stdin);
	if (result == -1)
	{
		if (feof(stdin))
			return (NULL);
		free(input);
		print_error();
	}
	input[strcspn(input, "\n")] = '\0';

	return (input);
}


/**
 * print_prompt - prints the command prompt for the shell
 */

void print_prompt(void)
{
	  write(STDOUT_FILENO, "#cisfun$ ", 10);
}

/**
 * main - gets input from user and executes the command
 *
 * @argc: arg count
 * @argv: array list of arg variables
 * @envp: list of environment variables
 *
 * Description: run an infinte loop for the custom shell's
 * command prompt. get input from user, strip off the new line character
 * added at the end of user input. check if there's a current running process;
 * if none, execute command otherwise wait for completion then execute command;
 * in case of error, print error statement.
 *
 * Return: int
 */

int main(__attribute__((unused))int argc, char *argv[], char *envp[])
{
	char *line;

	while (1)
	{
		print_prompt();
		line = get_input();
		if (line == NULL)
			break;
		execute_cmd(line, argv, envp);
	}

	return (0);
}
