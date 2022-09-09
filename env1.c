#include "main.h"

/**
 * copy_info - copies info to create a new env or alias
 */

char *copy_info(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = _strlen(name);
	len_value = _strlen(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}

/**
 * set_env - sets an environment variable
 *
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @datash: data structure (environ)
 * Return: no return
 */
void set_env(char *name, char *value, data_sh *dsh)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; dsh->_environ[i]; i++)
	{
		var_env = _strdup(dsh->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(dsh->_environ[i]);
			dsh->_environ[i] = copy_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	dsh->_environ = _reallocdp(dsh->_environ, i, sizeof(char *) * (i + 2));
	dsh->_environ[i] = copy_info(name, value);
	dsh->_environ[i + 1] = NULL;
}

/**
 * _setenv - compares env variables names
 * with the name passed.
 * @datash: data relevant (env name and env value)
 *
 * Return: 1 on success.
 */
int _setenv(data_sh *dsh)
{

	if (dsh->args[1] == NULL || dsh->args[2] == NULL)
	{
		get_error(dsh, -1);
		return (1);
	}

	set_env(dsh->args[1], dsh->args[2], dsh);

	return (1);
}

/**
 * _unsetenv - deletes a environment variable
 *
 * @datash: data relevant (env name)
 *
 * Return: 1 on success.
 */
int _unsetenv(data_sh *dsh)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int i, j, k;

	if (dsh->args[1] == NULL)
	{
		get_error(dsh, -1);
		return (1);
	}
	k = -1;
	for (i = 0; dsh->_environ[i]; i++)
	{
		var_env = _strdup(dsh->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, dsh->args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		get_error(dsh, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; dsh->_environ[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = dsh->_environ[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(dsh->_environ[k]);
	free(dsh->_environ);
	dsh->_environ = realloc_environ;
	return (1);
}
