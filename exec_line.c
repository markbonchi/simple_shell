#include "main.h"

/**
 * exec_line - finds builtin commands
 */

int exec_line(data_sh *dsh)
{
	int (*builtin)(data_sh *dsh);

	if (dsh->args[0] == NULL)
		return (1);

	builtin = get_builtin(dsh->args[0]);

	if (builtin != NULL)
		return (builtin(dsh));

	return (cmd_exec(dsh));
}
