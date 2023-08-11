#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * main - splits a string
 *
 * Return: int
 */

int main(void)
{
	char str[] = "Very well then, say thank you!";
	char delimiters[] = " ,!";
	char *token = strtok(str, delimiters);

	while (token != NULL)
	{
		printf("%s\n", token);
		token = strtok(NULL, delimiters);
	}
	return (0);
}
