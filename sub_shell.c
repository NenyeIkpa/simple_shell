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
 * @env: the enviromental variables.
 *
 * Description: tokenises the the sub-PATH
 * directories of the enviromental variables.
 *
 * Return: head of the PATH list.
 */

path_llist *token_to_list(char **env)
{
	char *token;
	path_llist *head;
	int i = 0;

	head = NULL;
	while (env[i] != NULL)
	{
		if (_strncmp(env[i], "PATH", 4) == 0)
		{
			token = _strtok(env[i], "=, :");
			break;
		}
		i++;
	}

	while (token != NULL)
	{
		token = _strtok(NULL, "=, :");
		if (token != NULL && _strcmp(token, "PATH") != 0)
			add_node(&head, token);
	}

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
				return (validate_access(&curr, arg));
			}
		}
		closedir(dir);
		if (curr->next == NULL)
			break;
		curr = curr->next;
	}

	return (arg);
}

/**
 * validate_access - validates if user has
 * the rights of a user to execute a command
 *
 * @path: directory returned from function "search_path" to be validated
 * @arg: user input
 *
 * Description: validates if a user has the access rights to execute
 * a command
 *
 * Return: the complete execution path
 */

char *validate_access(path_llist **path, char *arg)
{
	struct stat dstat;
	int res;
	char *full_path;

	res = stat((*path)->dir, &dstat) && S_ISREG(dstat.st_mode) &&
		(dstat.st_mode & S_IXUSR);

	if (res == -1)
		return (NULL);
	full_path = concatenate((*path)->dir, "/", arg);
	return (full_path);
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
