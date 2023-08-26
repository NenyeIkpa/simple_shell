#include "shell.h"

/**
 * add_node - adds node to head position of a linked list.
 *
 * @head: the head node
 * @token: tokenised path saved into each node
 *
 * Description: adds a new node to the head of a
 * struct list with token saved to the new node.
 *
 * Return: new head node
 */

path_llist *add_node(path_llist **head, char *token)
{
	path_llist *node;
	char *token_copy;

	if (token == NULL)
		return (NULL);
	node  = malloc(sizeof(path_llist));
	if (node == NULL)
		return (NULL);
	token_copy = _strdup(token);

	if (*head == NULL)
	{
		*head = node;
		node->dir = token_copy;
		node->next = NULL;
	}
	else
	{
		node->dir  = token_copy;
		node->next = *head;
		*head = node;
	}

	return (*head);
}

/**
 * token_to_list - tokenisation for the PATH.
 *
 * Description: tokenises the the sub-PATH
 * directories of the enviromental variables.
 *
 * Return: head of the PATH list.
 */

path_llist *token_to_list(void)
{
	char *token, *path_dup;
	path_llist *head;
	int i = 0;

	head = NULL;
	while (environ[i] != NULL)
	{
		if (_strncmp(environ[i], "PATH", 4) == 0)
		{
			path_dup = _strdup(environ[i]);
			token = _strtok(path_dup, "=");
			break;
		}
		i++;
	}

	while (token != NULL)
	{
		token = _strtok(NULL, ":");
		if (token != NULL && _strcmp(token, "PATH") != 0)
			add_node(&head, token);
	}

	free(path_dup);
	return (head);
}

/**
 * search_path - searches through the PATH.
 *
 * @head: the head pointer of the linked list
 * @arg: the argument or command passed by user to be searched
 *
 * Description: searches through the list of directories in "PATH" of the
 * environmental variables for the command or argument passed by the user
 *
 * Return: command or argument passed
 */

char *search_path(path_llist **head, char *arg)
{
	DIR *dir;
	struct dirent *entry;
	path_llist *curr;
	char *full_path = NULL;

	curr = *head;
	while (curr != NULL)
	{
		dir = opendir(curr->dir);
		if (dir != NULL)
		while ((entry = readdir(dir)) != NULL)
		{
			if (_strcmp(entry->d_name, arg) == 0)
			{
				closedir(dir);
				if (validate_access(curr->dir) == 0)
				{
					full_path = concatenate(curr->dir, "/", arg);
					return (full_path);
				}
			}
		}
		closedir(dir);
		if (curr->next == NULL)
			break;
		curr = curr->next;
	}

	return (full_path);
}

/**
 * validate_access - validates if user has
 * the rights of a user to execute a command
 *
 * @path: path to be validated
 *
 * Description: validates if a user has the access rights to execute
 * a command
 *
 * Return: 0 when user has execution rights, otherwise, 1
 */

int validate_access(char *path)
{
	struct stat dstat;
	int res;

	res = stat(path, &dstat);
	if (res == -1)
		return (1);
	return (0);
}

/**
 * concatenate - concatenates 3 strings
 *
 * @s1: 1st string to be concatenated
 * @s2: 2nd string to be concatenated
 * @s3: 3rd string to be concatenated
 *
 * Description: concatenates 3 strings into 1 string.
 *
 * Return: the concatenated string
 */

char *concatenate(char *s1, char *s2, char *s3)
{
	int size = _strlen(s1) + _strlen(s2) + _strlen(s3) + 1;
	char *str;

	str = malloc(size);
	if (str == NULL)
		return (NULL);
	_strcpy(str, s1);
	_strcat(str, s2);
	_strcat(str, s3);

	return (str);
}
