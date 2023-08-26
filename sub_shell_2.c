#include "shell.h"

/**
 * print_prompt - display's user command prompt
 */

void print_prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "#cisfun$ ", 9);
}

/**
 * delete_list - deletes a linked list
 *
 * @head: head ptr to list
 */

void delete_list(path_llist *head)
{
	path_llist *temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->dir);
		free(temp);
	}
	free(head);
}


/**
 * handle_comments - checks if the string is a comment
 *
 * @input: string to be checked. fix a null byte at point of #
 */

void handle_comments(char *input)
{
	int i = 0;

	while (input[i])
	{
		if (i > 0 && input[i] == '#' && input[i - 1] != ' ')
			break;

		if (input[i] == '#')
		{
			input[i] = '\0';
			break;
		}

		i++;
	}
}

/**
 * reverse_str - reverses a string
 *
 * @str: given string
 */

void reverse_str(char *str)
{
	int start = 0, length = _strlen(str), end = length - 1;
	char temp;

	while (start < end)
	{
		temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
}

/**
 * _itoa - converts integer to string
 *
 * @num: given number
 * @str: buffer to hold converted num
 * @base: base of conversion
 *
 * Return: string
 */

char *_itoa(int num, char *str, int base)
{
	int is_negative = 0, i = 0, rem;

	/* handle 0 explicitly, otherwise empty string is printed */
	if (num == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}

    /* handle negative numbers for base 10 */
	if (num < 0 && base == 10)
	{
		is_negative = 1;
		num = -num;
	}
	while (num != 0)
	{
		rem = num % base;
		str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
		num = num / base;
	}

	/* append negative sign for base 10 */
	if (is_negative)
		str[i++] = '-';
	str[i] = '\0';

	/* reverse the string */
	reverse_str(str);

	return (str);
}
