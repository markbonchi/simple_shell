#include "main.h"

/**
 * is_cdir - checks ":" if is in current directory
 */

int is_cdir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
		*i += 1;

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * _which - locates a command
 */

char *_which(char *cmd, char **_environ)
{
	char *path, *ptr_path, *token_path, *dir;
	int ;en_dir, len_cmd, i;
	struct stat st;

	path = _getenv("PATH", _environ);
	if (path)
	{
		ptr_path = _strdup(path);
		len_cmd = _strlen(cmd);
		token_path = _strtok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (is_cdir(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = _strlen(token_path);
			dir = malloc(len_sir + len_cmd + 2);
			_strcpy(dir, token_path);
			_strcpy(dir, "/");
			_strcpy(dir, cmd);
			_strcpy(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = _strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * is_executable - determines if is executable
 */

int is_executable(data_sh *dsh)
{
	struct stat st;
	int i;
	char *input;

	input = dsh->args[0];
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		} else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		} else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(input + i, &st) == 0)
		return (i);

	get_error(dsh, 127);
	return (-1);
}

/**
 * check_error_cmd - verifies if user has permission to access
 */

int check_error_cmd(char *dir, data_sh *dsh)
{
	if (dir == NULL)
	{
		get_error(dsh, 127);
		return (1);
	}

	if (_strcmp(dsh->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_error(dsh, 126);
			free(dir);
			return (1);
		}
		free(dir);
	} else
		if (access(dsh->args[0], X_OK) == -1)
		{
			get_error(dsh, 126);
			return (1);
		}

	return (0)
}

/**
 * cmd_exec - execute command lines
 */

int cmd_exec(data_sh *dsh)
{
	pid_t pd, wpd;
	int state, exec;
	char *dir;
	(void) wpd;

	exec = is_executable(dsh);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = _which(dsh->args[0], dsh->_environ);
		if (check_error_cmd(dir, dsh) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = _which(dsh->args[0], dsh->_environ);
		else
			dir = dsh->args[0];
		execve(dir + exec, dsh->args, dsh->environ);
	} else if (pd < 0)
	{
		perror(dsh->av[0]);
		return (1);
	} else
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));

	dsh->status = state / 256;
	return (1);
}

