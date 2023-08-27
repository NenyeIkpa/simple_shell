#include "shell.h"

int _chdir(char **argv);
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
	int i = 0;
	char new_dir[MAX_PATH_LENGTH], old_dir[MAX_PATH_LENGTH];
	const char *home_dir, *prev_dir;

	while (argv[i] != NULL)
		i++;
	if (i == 1)
	{
		home_dir = getenv("HOME");
		if (home_dir == NULL)
		{
			return (1);
		}
		_strcpy(new_dir, (char *)home_dir);
	}
	else if (i == 2)
	{
		if (_strcmp(argv[1], "-") == 0)
		{
			prev_dir = getenv("OLDPWD");
			if (prev_dir == NULL)
			{
				return (1);
			}
			_strcpy(new_dir, argv[1]);
		}
		else
			_strcpy(new_dir, argv[1]);
	}
	else
	{
		return (1);
	}
	if (getcwd(old_dir, sizeof(old_dir)) == NULL)
	{
		return (1);
	}
	if (chdir(new_dir) != 0)
	{
		_puts(prgm_name);
		_puts(": 1: cd: can't cd to");
		_puts(argv[1]);
		return (1);
	}
	if (setenv("OLDPWD", old_dir, 1) != 0)
	{
		return (1);
	}
	if (setenv("PWD", new_dir, 1) != 0)
	{
		return (1);
	}
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
