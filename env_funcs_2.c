#include "shell.h"

int _putenv(char *str);

/**
 * printenv - prints the environ variables
 */

void printenv(void)
{
	size_t i = 0;
	char *v;

	while (environ[i] != NULL)
	{
		v = _strdup(environ[i]);
		_putstring(v);
		_putstring("\n");
		free(v);
		i++;
	}
	environ_size = i;
}

/**
 * _chdir - funcion that handles change of directory
 *
 * @argv: list of args
 *
 * Return: int
 */

int _chdir(char **argv)
{
	int argc = 0;
	char current_dir[MAX_PATH_LENGTH];
	char *home_dir = getenv("HOME");
	char *previous_dir = NULL, *target_dir = NULL;

	while (argv[argc] != NULL)
		argc++;
	if (argc > 2)
		return (1);
	if (argc == 1)
	{
		if (home_dir == NULL)
			return (1);
		if (getcwd(current_dir, sizeof(current_dir)) == NULL)
			return (1);
		if (chdir(home_dir) != 0)
			return (1);
	}
	else
	{
		target_dir = argv[1];
		if (_strcmp(target_dir, "-") == 0)
		{
			if (previous_dir == NULL)
				return (1);
			target_dir = previous_dir;
		}
		if (getcwd(current_dir, sizeof(current_dir)) == NULL)
			return (1);
		if (chdir(target_dir) != 0)
		{
			_puts(prgm_name);
			_puts(": 1: cd: can't cd to ");
			_puts(target_dir);
			_puts("\n");
			return (1);
		}
		previous_dir = _strdup(current_dir);
	}
	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
		return (1);
	/* Update the PWD environment variable */
	if (setenv("PWD", current_dir, 1) != 0)
		return (1);
	return (0);
}

/**
 * _putenv2 - adds an env variable to environ
 *
 * @str: variable to be added
 *
 * Return: int
 */

int _putenv2(char *str)
{
	char *str_dup, *env_name, **new_environ;
	int i = 0;

	if (str == NULL || strchr(str, '=') == NULL)
		return (-1);
	str_dup = _strdup(str);
	if (str_dup == NULL)
		return (-1);
	env_name = _strtok(str_dup, "=");
	while (environ[i] != NULL)
	{
		if (_strncmp(environ[i], env_name, _strlen(env_name)) == 0 &&
				environ[i][_strlen(env_name)] == '=')
		{
			free(environ[i]);
			environ[i] = _strdup(str);
			free(str_dup);
			return (0);
		}
		i++;
	}

	/* If the variable doesn't exist, add it to the environment */
	new_environ = (char **)malloc((environ_size + 2) * sizeof(char *));
	if (new_environ == NULL)
	{
		free(str_dup);
		return (-1);
	}

	/* Copy existing environment variables */
	for (i = 0; environ[i] != NULL; i++)
		new_environ[i] = environ[i];

	/* Add the new variable */
	new_environ[environ_size] = str_dup;
	new_environ[environ_size + 1] = NULL;

	/* Update the environ pointer to point to the new environment */
	environ = new_environ;
	environ_size++;

	return (0);
}
