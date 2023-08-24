#include "shell.h"

/**
 * _strdup - duplicates given string
 *
 * @str: given string
 *
 * Return: string duplicate
 */

char *_strdup(char *str)
{
	int i, len = 0;
	char *dup;

	len = _strlen(str);
	dup = malloc(sizeof(char *) * len);
	if (dup == NULL)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		dup[i] = str[i];
	dup[i] = '\0';

	return (dup);
}

/**
 * _strtok - tokenizes given string
 *
 * @s: given string
 * @delim: string of delimiting characters
 *
 * Return: token
 */

char *_strtok(char *s, const char *delim)
{
	static char *last_token;
	char *token, *delimiter;

	if (s != NULL)
		last_token = s;
	if (last_token == NULL)
		return (NULL);

	token = last_token;
	while (*last_token != '\0')
	{
		delimiter = (char *)delim;
		while (*delimiter != '\0')
		{
			if (*last_token == *delimiter)
			{
				*last_token = '\0';
				last_token++;
				if (token == last_token - 1)
				{
					token = last_token;
					continue;
				}
				return (token);
			}
			delimiter++;
		}
		last_token++;
	}
	if (token == last_token)
		return (NULL);
	return (token);
}
