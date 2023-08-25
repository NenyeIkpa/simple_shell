#include "shell.h"

/**
 * _putstring - prints string to stdout
 *
 * @s: given string
 */

void _putstring(char *s)
{
	int i = 0;

	while (s[i] != '\0')
	{
		_putchar(s[i]);
		i++;
	}
}
