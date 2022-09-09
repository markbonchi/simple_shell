#include "main.h"

/**
 * strcat_cd - concatenates the message of cd error
 */

char *strcat_cd(data_sh *dsh, char *msg, char *error, char *ver_str)
{
	char *illegal_flag;

	_strcpy(error, dsh->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, dsh->args[0]);
	_strcat(error, msg);
	if (dsh->args[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = dsh->args[1][1];
		illegal_flag[2] = '\0';
		_strcat(error, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		_strcat(error, dsh->args[1]);
	}

	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}

/**
 * error_get_cd - error message for cd command in get_cd
 */

char *error_get_cd(data_sh *dsh)
{
	int length, len_id;
	char *error, *ver_str, *msg;

	ver_str = aux_itoa(dsh->counter);
	if (dsh->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlen(dsh->args[1]);
	}

	length = _strlen(dsh->av[0]) + _strlen(dsh->args[0]);
	length += _strlen(ver_str) + _strlen(msg) + len_id + 5;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}

	error = strcat_cd(dsh, msg, error, ver_str);

	free(ver_str);

	return (error);
}

/**
 * error_not_found - generic error message for command not found
 */

char *error_not_found(data_sh *dsh)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = aux_itoa(dsh->counter);
	length = _strlen(dsh->av[0]) + _strlen(ver_str);
	length += _strlen(dsh->args[0]) + 16;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, dsh->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, dsh->args[0]);
	_strcat(error, ": not found\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}

/**
 * error+exit_shell - errormessage for exit in get_exit
 */

char *error_exit_shell(data_sh *dsh)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = aux_itoa(dsh->counter);
	length = _strlen(dsh->av[0]) + _strlen(ver_str);
	length += _strlen(dsh->args[0]) + _strlen(dsh->args[1]) + 23;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, dsh->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, dsh->args[0]);
	_strcat(error, ": Illegal number: ");
	_strcat(error, dsh->args[1]);
	_strcat(error, "\n\0");
	free(ver_str);

	return (error);
}

/**
 * error_env - error message for env in get_env
 */

char *error_env(data_sh *dsh)
{
	int length;
	char *error;
	char *ver_str;
	char *msg;

	ver_str = aux_itoa(dsh->counter);
	msg = ": Unable to add/remove from environment\n";
	length = _strlen(dsh->av[0]) + _strlen(ver_str);
	length += _strlen(dsh->args[0]) + _strlen(msg) + 4;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}

	_strcpy(error, dsh->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, dsh->args[0]);
	_strcat(error, msg);
	_strcat(error, "\0");
	free(ver_str);

	return (error);
}

/**
 * error_path_126 - error message for path and failure denied permission
 */

char *error_path_126(data_sh *dsh)
{
	int length;
	char *ver_str;
	char *error;

	ver_str = aux_itoa(dsh->counter);
	length = _strlen(dsh->av[0]) + _strlen(ver_str);
	length += _strlen(dsh->args[0]) + 24;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, dsh->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, dsh->args[0]);
	_strcat(error, ": Permission denied\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}

