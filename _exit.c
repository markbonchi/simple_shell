#include "main.h"

/**
 * exit_shell - exits the shell
 */

int exit_shell(data_sh *dsh)
{
	unsigned int ustatus;
	int is_digit;
	int str_len;
	int big_number;

	if (dsh->args[1] != NULL)
	{
		ustatus = _atoi(dsh->args[1]);
		is_digit = _isdigit(dsh->args[1]);
		str_len = _strlen(dsh->args[1]);
		big_number = ustatus > (unsigned int)INT_MAX;
		if (!is_digit || str_len > 10 || big_number)
		{
			get_error(dsh, 2);
			dsh->status = 2;
			return (1);
		}
		dsh->status = (ustatus % 256);
	}
	return (0);
}
