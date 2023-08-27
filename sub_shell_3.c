#include "shell.h"

/**
 * handle_builtins - handles the execution of built in functions
 *
 * @argv: arg list
 * @head: pointer to head pointer of a list
 * @line: pointer to input
 *
 * Return: int
 */

int handle_builtins(char **argv, path_llist **head, char *line);

int handle_builtins(char **argv, path_llist **head, char *line)
{
	int argc = 0;

	while (argv[argc] != NULL)
		argc++;

	if (_strcmp(argv[0], "exit") == 0)
	{
		if (argc == 1)
		{
			delete_list(*head);
			free(line);
			exit(err_status);
		}
		else if (argc == 2)
		{
			err_status = atoi(argv[1]);
			handle_err_status(err_status, head, line, argv);
		}
		else
			return (1);
	}
	else if (_strcmp(argv[0], "env") == 0)
	{
		if (argc == 1)
		{
			printenv();
			free(line);
		}
		else
			return (1);
	}
	/*
	 * else if (_strcmp(argv[0], "setenv") == 0)
	 * {
	 * if (argc == 2)
			_setenv(argv[1], argv[2], 1);
		else
			return (1);
	}
	*/
	else if (_strcmp(argv[0], "cd") == 0)
	{
		_chdir(argv);
		free(line);
	}
	else
		return (5);
	return (0);
}

/**
 * handle_err_status - handles exit codes
 *
 * @err_status: exit code
 * @head: head pointer to list
 * @line: given input
 * @argv: list of args
 *
 * Return: int
 */

int handle_err_status(int err_status, path_llist **head,
		char *line, char **argv)
{
	if (err_status < 0)
	{
		_puts(prgm_name);
		_puts(": 1: exit: Illegal number: ");
		_puts(argv[1]);
		_puts("\n");
		delete_list(*head);
		free(line);
		exit(2);
	}
	else if (argv[1][0] != '0' && atoi(argv[1]) == 0)
	{
		_puts(prgm_name);
		_puts(": 1: exit: Illegal number: ");
		_puts(argv[1]);
		_puts("\n");
		delete_list(*head);
		free(line);
		exit(2);
	}
	else
	{
		delete_list(*head);
		free(line);
		exit(err_status);
	}
	return (0);
}
