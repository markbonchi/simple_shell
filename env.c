#include "main.h"

/**
 * cmp_env_name - compares env variables
 */

int cmp_env_name(const char *nenv, const char *name)
{
	int i;

	for (i = 0; nenv[i] != '='; i++)
		if (nenv[i] != name[i])
			return (0);

	return (i + 1);
}

/**
 * _getenv - get an environment variable
 */

char *_getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int i, mov;

	/* initiate ptr_env value */
	ptr_env = NULL;
	mov = 0;

	/* compare environment variables ( environ declared in header)*/
	for (i = 0; _environ[i]; i++)
	{
		mov = cmp_env_name(_environ[i], name);
		if (mov)
		{
			ptr_env = _environ[i];
			break;
		}
	}
	return (ptr_env + mov);
}

/**
 * _env - print the environment variables
 */

int _env(data_sh *dsh)
{
	int i, j;

	for (i = 0; dsh->_environ[i]; i++)
	{
		j = 0;
		while (dsh->_environ[i][j])
			j++;
		write(STDOUT_FILENO, dsh->_enviorn[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	dsh->status = 0;

	return (1);
}

