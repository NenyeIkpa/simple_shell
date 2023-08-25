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
