#include "main.h"

/**
 * get_help - function that retrieves help messages according builtin
 * @dsh: data structure
 * Return: Return 0
*/

int get_help(data_sh *dsh)
{

	if (dsh->args[1] == 0)
		aux_help_general();
	else if (_strcmp(dsh->args[1], "setenv") == 0)
		aux_help_setenv();
	else if (_strcmp(dsh->args[1], "env") == 0)
		aux_help_env();
	else if (_strcmp(dsh->args[1], "unsetenv") == 0)
		aux_help_unsetenv();
	else if (_strcmp(dsh->args[1], "help") == 0)
		aux_help();
	else if (_strcmp(dsh->args[1], "exit") == 0)
		aux_help_exit();
	else if (_strcmp(dsh->args[1], "cd") == 0)
		aux_help_cd();
	else if (_strcmp(dsh->args[1], "alias") == 0)
		aux_help_alias();
	else
		write(STDERR_FILENO, dsh->args[0],
		      _strlen(dsh->args[0]));

	dsh->status = 0;
	return (1);
}
