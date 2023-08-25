#include "shell.h"

/**
 * print_prompt - display's user command prompt
 */

void print_prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "#cisfun$ ", 9);
}

/**
 * delete_list - deletes a linked list
 *
 * @head: head ptr to list
 */

void delete_list(path_llist *head)
{
	path_llist *temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->dir);
		free(temp);
	}
	free(head);
}


/**
 * handle_comments - checks if the string is a comment
 *
 * @input: string to be checked. fix a null byte at point of #
 */

void handle_comments(char *input)
{
	int i = 0;

	while (input[i])
	{
		if (i > 0 && input[i] == '#' && input[i - 1] != ' ')
			break;

		if (input[i] == '#')
		{
			input[i] = '\0';
			break;
		}

		i++;
	}
}
