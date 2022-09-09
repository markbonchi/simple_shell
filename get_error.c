#include "main.h"

/**
 * get_error - calls the error according to the builtin syntax or permission
 */

int get_error(data_sh *dsh, int eval)
{
	char *error;

	switch (eval)
	{
	case -1:
		error = error_env(dsh);
		break;
	case 126:
		error = error_path_126(dsh);
		break;
	case 127:
		error = error_not_found(dsh);
		break;
	case 2:
		if (_strcmp("exit", dsh->args[0]) == 0)
			error = error_exit_shell(dsh);
		else if (_strcmp("cd", dsh->args[0]) == 0)
			error = error_get_cd(dsh);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	dsh->status = eval;
	return (eval);
}
