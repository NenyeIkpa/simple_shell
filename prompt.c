#include <stdio.h>
#include <stdlib.h>

/**
 * main - gets input from user and prints it
 *
 * Return: int
 */

int main(void)
{
	char *line = NULL;
	size_t linecap = 0;
	ssize_t linelen;

	while (1)
	{
		printf("$");
		linelen = getline(&line, &linecap, stdin);
		if (linelen == -1)
		{
			if (feof(stdin))
				break;
			exit(EXIT_FAILURE);
		}
		printf("%s", line);
	}
	free(line);

	exit(EXIT_SUCCESS);
}
