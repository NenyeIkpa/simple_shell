#include "shell.h"

/**
 * _getenv - gets env variable
 *
 * @envv: name of env variable
 *
 * Return: env variable or NULL
 */

char *_getenv(char *envv)
{
	int i = 0, len;

	len = _strlen(envv);
	while (environ[i] != NULL)
	{
		if (_strncmp(environ[i], envv, len) == 0)
			return (environ[i]);
		i++;
	}
	return (NULL);
}

/**
 * _putenv - adds an env to environ
 *
 * @new_env: new env to be added
 *
 * Return: int
 */

int _putenv(char *new_env)
{
	int i = 0;

	while (environ[i] != NULL)
		i++;
	environ[i] = new_env;
	environ[i + 1] = NULL;
	return (0);
}

/**
 * _unsetenv - deletes an env variable
 *
 * @envv: env variable to be deleted
 *
 * Return: int
 */

int _unsetenv(char *envv)
{
	int i = 0, j = 0;
	char *env;

	env = _getenv(envv);
	while (environ[i] == NULL)
	{
		if (_strcmp(environ[i], env) == 0)
		{
			j = i + 1;
			while (environ[j] != NULL)
			{
				environ[i] = environ[j];
				i++;
				j++;
			}
			free(environ[i]);
			environ[i] = NULL;
			return (0);
		}
		i++;
	}
	return (1);
}

/**
 * _replaceenv - replaces the value of an existing env variable
 *
 * @envv: env variable name
 * @replacant: the replacement for the env variable
 *
 * Return: int
 */

int  _replaceenv(char *envv, char *replacant)
{
	int i = 0, len = 0;

	len = _strlen(envv);
	while (environ[i] == NULL)
	{
		if (_strncmp(environ[i], envv, len) == 0)
		{
			free(environ[i]);
			environ[i] = replacant;
			return (0);
		}
		i++;
	}
	return (1);
}

/**
 * _setenv -  sets an env variable
 *
 * @name: name of env variable
 * @value: value of env variable
 * @overwrite: 0 for no, >0 for yes
 *
 * Return: int
 */

int _setenv(char *name, char *value, int overwrite)
{
	char *existing_value = getenv(name), *new_entry;

	/*
	 * If the variable exists and overwrite is not allowed,
	 * return without modifying
	 */
	if (existing_value && !overwrite)
		return (0);

	/* If the variable doesn't exist or overwrite is allowed, set the new value */
	new_entry = concatenate(name, "=", value);
	if (!new_entry)
		return (-1);
	if (overwrite)
		_replaceenv(name, new_entry);
	else
		_putenv(new_entry);

	return (0);
}
