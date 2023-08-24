#include "shell.h"

/**
 * _strlen - counts the length of a string
 *
 * @str: given string
 *
 * Return: length of a string
 */

int _strlen(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; )
		i++;
	return (i);
}

/**
 * _strcmp - checks if two strings are same
 *
 * @s1: given string
 * @s2: given string
 *
 * Return: 0 if true, 1 if false
 */

int _strcmp(char *s1, char *s2)
{
	int i;

	if (s1 == NULL || s2 == NULL || (_strlen(s1) != _strlen(s2)))
		return (1);
	for (i = 0; s1[i] != '\0'; i++)
	{
		if (s1[i] != s2[i])
			return (1);
	}
	return (0);
}

/**
 * _strncmp - compares two strings up to n bytes
 *
 * @s1: given string
 * @s2: given string
 * @n: number of bytes to be compared
 *
 * Return: 0 if true, 1 when false
 */

int _strncmp(char *s1, char *s2, size_t n)
{
	size_t i;

	if (s1 == NULL || s2 == NULL)
		return (1);
	for (i = 0; i < n; i++)
	{
		if (s1[i] != s2[i])
			return (1);
	}
	return (0);
}

/**
 * _strcpy - copies one string to another
 *
 * @s1: source string
 * @s2: destination string
 *
 * Return: destination string with copied content
 */

char *_strcpy(char *s2, char *s1)
{
	int i;

	for (i = 0; s1[i] != '\0'; i++)
		s2[i] = s1[i];
	s2[i] = '\0';
	return (s2);
}

/**
 * _strcat - concatenates two strings
 *
 * @s1: first and destination string
 * @s2: second string
 *
 * Return: destination string
 */

char *_strcat(char *s1, char *s2)
{
	int i, dest_len;

	dest_len = _strlen(s1);
	for (i = 0; s2[i] != '\0'; i++)
		s1[dest_len + i]  = s2[i];

	s1[dest_len + i] = '\0';
	return (s1);
}

