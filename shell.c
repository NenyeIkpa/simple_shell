#include "shell.h"

int main(__attribute__((unused))int argc, char *argv[], char *envp[]);

/**
 * print_error_B - prints error in non-interactive mode
 */

void print_error_B(void)
{
	write(STDERR_FILENO, prgm_name, strlen(prgm_name));
	write(STDERR_FILENO, ": 1: ", 5);
	write(STDERR_FILENO, arg, strlen(arg));
	write(STDERR_FILENO, ": not found\n", 12);
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

	token = _strtok(*iptr, " ");
	if (token == NULL)
		return (-1);
	while (token != NULL)
	{
		argv[i] = token;
		i++;
		token = _strtok(NULL, " ");
	}
	argv[i] = NULL;
	return (0);
}

/**
 * execute_command - executes command
 *
 * @command: input from stdin
 * @argv: list of arg variables
 * @envp: list of env variables
 *
 * Description: forks current process. executes command
 * if no running process otherwise waits for completion
 * of running process before execution.
 *
 * Return: 0 for success -1 for failure
 */

int execute_command(char *command, char **argv, char **envp)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(command, argv, envp) == -1)
			return (-1);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		print_error();

	return (0);
}

/**
 * main - gets input from user and executes the command
 *
 * @argc: arg count
 * @argv: list of arg variables
 * @envp: list of environment variables
 *
 * Description: run an infinte loop for the custom shell's
 * command prompt. get input from user, strip off the new line character
 * added at the end of user input. check if there's a current running process;
 * if none, execute command otherwise wait for completion then execute command;
 * in case of error, print error statement.
 *
 * Return: success 0, failure -1
 */

int main(__attribute__((unused))int argc, char *argv[], char *envp[])
{
	char *line = {NULL}, *path = NULL;
	size_t size = 0;
	ssize_t linelen = 0;
	path_llist *head;

	head = token_to_list(envp);
	prgm_name = argv[0];
	while (1)
	{
		if (isatty(STDIN_FILENO))
			print_prompt();
		linelen = getline(&line, &size, stdin);
		if (linelen == -1)
		{
			if (feof(stdin))
				break;
			print_error();
		}
		line[linelen - 1] = '\0';
		if (strcmp(line, "exit") == 0)
			break;
		if (handle_args(&line, argv) != -1)
		{
			arg = argv[0];
			path = search_path(&head, argv[0]);
			if ((execute_command(path, argv, envp)) == -1)
			{
				print_error();
				if (head != NULL)
					delete_list(head);
				free(line);
				exit(EXIT_FAILURE);
			}
			if (path != argv[0])
				free(path);
		}
	}
	if (head != NULL)
		delete_list(head);
	free(line);
	return (0);
}
