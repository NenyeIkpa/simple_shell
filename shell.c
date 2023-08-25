#include "shell.h"

int main(__attribute__((unused))int argc, char *argv[], char *envp[]);

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
	int status, exit_status;

	pid = fork();
	if (pid == 0)
	{
		execve(command, argv, envp);
			return (-1);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
		errno = exit_status;
	}
	else
		exit(-1);

	return (0);
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

void handle_args(char **iptr, char **argv)
{
	char *token = NULL;
	int i = 0;

	token = _strtok(*iptr, " ");

	while (token != NULL)
	{
		if (_strcmp(token, "") != 0)
			argv[i] = token;
		i++;
		token = _strtok(NULL, " ");
	}
	argv[i] = NULL;
}

/**
 * get_input - gets input from user
 *
 * Return: input
 */

char *get_input(void)
{
	char *input = NULL;
	size_t size = 0;
	ssize_t inputlen = 0;
	int interactive = isatty(STDIN_FILENO);

	inputlen = getline(&input, &size, stdin);
	if (inputlen == -1)
	{
		/** check for Ctrl->D */
		if (feof(stdin))
		{
			free(input);
			if (interactive)
				_putchar('\n');
			return (NULL);
		}
		free(input);
		print_error();
		exit(errno);
	}
	return (input);
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
	char *line, *path = NULL;
	path_llist *head;
	int count = 0, interactive;
	errno = 0;

	head = token_to_list(envp);
	prgm_name = argv[0];
	interactive = isatty(STDIN_FILENO);
	while (1)
	{
		count++;
		if (interactive)
			print_prompt();
		line = get_input();
		if (line == NULL)
			break;
		line[_strlen(line) - 1] = '\0';
		if (strcmp(line, "exit") == 0)
			break;
		handle_args(&line, argv);
		if (argv[0] == NULL)
		{
			free(line);
			continue;
		}
		arg = argv[0];
		if (validate_access(argv[0]) == 1)
		{;
			path = search_path(&head, argv[0]);
			if (path == NULL)
			{
				cmd_count  = count + '0';
				print_error();
				free(line);
				if (!interactive)
					exit(127);
				continue;
			}
		}
		else
			path = argv[0];
		if ((execute_command(path, argv, envp)) == -1)
		{
			print_error();
			if (head != NULL)
				delete_list(head);
			free(line);
			exit(2);
		}
		if (path != argv[0])
			free(path);
	free(line);
	}
	if (head != NULL)
		delete_list(head);
	free(line);
	return (0);
}
