#include "shell.h"

/**
 * print_error_A - prints error in interactive mode
 */

void print_error_A(void)
{
	perror(prgm_name);
}

/**
 * print_error_B - prints error in non-interactive mode
 */

void print_error_B(void)
{
	_puts(prgm_name);
	_puts(": 1: ");
	_puts(arg);
	_puts(": not found\n");
}

/**
 * print_error - prints error messages
 */

void print_error(void)
{
	if (isatty(STDIN_FILENO))
		print_error_A();
	else
		print_error_B();
}
