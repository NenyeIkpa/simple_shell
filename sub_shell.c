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

path_llist *add_node(path_llist **head,  const char *token)
{
	path_llist *node;
	char *token_copy;

	if (token == NULL)
		return (NULL);
	node  = malloc(sizeof(node));
	if (node == NULL)
		return (NULL);
	token_copy = strdup(token);
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
		if (strncmp(env[i], "PATH", 4) == 0)
		{
			token = strtok(env[i], "=");
			break;
		}
		i++;
	}

	while (token != NULL)
	{
		token = strtok(NULL, ":");
		if (token != NULL && strcmp(token, "PATH") != 0)
			add_node(&head, token);
	}

	return (head);
}

/**
 * search_path -
 *
 * @head:
 * @arg:
 *
 * Description:
 *
 * Return:
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
			if (strcmp(entry->d_name, arg) == 0)
				return (validate_access(&curr, arg));
		}
		closedir(dir);
		if (curr->next == NULL)
			break;
		curr  = curr->next;
	}

	return (arg);
}

/**
 * validate_access -
 *
 * @path:
 * @arg:
 *
 * Description:
 *
 * Return:
 */

char *validate_access(path_llist **path, char *arg)
{
	struct stat dstat;
	int res;
	char *full_path;

	res = stat((*path)->dir, &dstat) && S_ISREG(dstat.st_mode) && (dstat.st_mode & S_IXUSR);
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
	int size = strlen(s1) + strlen(s2) + strlen(s3) + 1;
	char *str = malloc(size);

	strcpy(str, s1);
	strcat(str, s2);
	strcat(str, s3);

	return (str);
}
