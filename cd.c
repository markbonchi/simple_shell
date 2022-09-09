#include "main.h"

/**
 * cd_dot - changes to present dir
 */

void cd_dot(data_sh *dsh)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, dsh);
	dir = dsh->args[1];
	if (_strcmp(".", dir) == 0)
	{
		set_env("PWD", cp_pwd, dsh);
		free(cp_pwd);
		return;
	}
	if (_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	rev_string(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			rev_string(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_env("PWD", cp_strtok_pwd, dsh);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", dsh);
	}
	dsh->status = 0;
	free(cp_pwd);
}

/**
 * cd_to - changes to a givne directory
 */

void cd_to(data_sh *dsh)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = dsh->args[1];
	if (chdir(dir) == -1)
	{
		get_error(dsh, 2);
		return;
	}

	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, dsh);

	cp_dir = _strdup(dir);
	set_env("PWD", cp_dir, dsh);

	free(cp_pwd);
	free(cp_dir);

	dsh->status = 0;

	chdir(dir);
}


/**
 * cd_previous - changes to previous directory
 */

void cd_previous(data_sh *dsh)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	p_oldpwd = _getenv("OLDPWD", dsh->_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	set_env("OLDPWD", cp_pwd, dsh);

	if (chdir(cp_oldpwd) == -1)
		set_env("PWD", cp_pwd, dsh);
	else
		set_env("PWD", cp_oldpwd, dsh);

	p_pwd = _getenv("PWD", dsh->_environ);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	dsh->status = 0;

	chdir(p_pwd);
}

/**
 * cd_to_home - changes to home dir
 */

void cd_to_home(data_sh *dsh)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	home = _getenv("HOME", dsh->_environ);

	if (home == NULL)
	{
		set_env("OLDPWD", p_pwd, dsh);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(dsh, 2);
		free(p_pwd);
		return;
	}

	set_env("OLDPWD", p_pwd, dsh);
	set_env("PWD", home, dsh);
	free(p_pwd);
	dsh->status = 0;
}
