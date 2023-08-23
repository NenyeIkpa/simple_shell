#include "shell.h"

/**
 * print_prompt - display's user command prompt
 */

void print_prompt(void)
{
	write(STDOUT_FILENO, "#cisfun$ ", 9);
}


/**
 * print_error_A - prints error in interactive mode
 */

void print_error_A(void)
{
	perror(prgm_name);
}
