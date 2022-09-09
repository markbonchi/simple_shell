#include "main.h"

/**
 * cd_shell - change es current directory
 */

int cd_shell(data_sh *dsh)
{
	char *dir;
	int ishome, ishome2, isddash;

	dir = dsh->args[1];

	if (dir != NULL)
	{
		ishome = _strcmp("$HOME", dir);
		ishome2 = _strcmp("~", dir);
		isddash = _strcmp("--", dir);
	}

	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		cd_to_home(dsh);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		cd_previous(dsh);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cd_dot(dsh);
		return (1);
	}

	cd_to(dsh);

	return (1);
}
