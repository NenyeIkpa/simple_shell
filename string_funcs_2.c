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
	for (i = 0; str[i] != '\0'; i++)
		dup[i] = str[i];
	dup[i] = '\0';

	return (dup);
}
