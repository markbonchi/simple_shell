#include "main.h"

/**
 * free_data - frees data structure
 */

void free_data(data_sh *dsh)
{
	unsigned int i;

	for (i = 0; dsh->_environ[i]; i++)
		free(dsh->_environ[i]);
	free(dsh->_environ);
	free(dsh->pid);
}

/**
 * set_data - initializes data structure
 */

void set_data(data_sh *dsh, char **av)
{
	unsigned int i;

	dsh->av = av;
	dsh->input = NULL;
	dsh->args = NULL;
	dsh->status = 0;
	dsh->counter = 1;

	i = 0;
	while(environ[i])
		i++;

	dsh->_environ = malloc(sizeof(char *) * (i + 1));
	for (i = 0; environ[i]; i++)
	{
		dsh->_environ[i] = _strdup(environ[i]);
	}
	dsh->_environ[i] = NULL;
	dsh->pid = aux_itoa(getpid());
}

/**
 * main - Entry point
 */

int main(int ac, char **av)
{
	data_sh dsh;
	(void) ac;

	signal(SIGINT, get_sigint);
	set_data(&dsh, av);
	shell_loop(&dsh);
	free_data(&dsh);
	if (dsh.status < 0)
		return (255);
	return (dsh.status);
}
