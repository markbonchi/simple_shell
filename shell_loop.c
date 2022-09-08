#include "main.h"

/**
 * without_comment - deletes comments from the input
 */

char *without_comment(char *in)
{
	int i, upto;

	upto = 0;
	for (i = 0; in[i]; i++)
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}
			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				upto = i;
		}
	if (upto != 0)
	{
		in = _realloc(in, i, upto + 1);
		in[upto] = '\0';
	}
	return (in);
}

/**
 * shell_loop - Loop
 */

void shell_loop(data_sh *dsh)
{
	int loop, i_eof;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "$ ", 2);
		input = _readline(&i_eof);
		if (i_eof != -1)
		{
			input = without_comment(input);
			if (input == NULL)
				continue;
			if (check_syntax_error(dsh, inout) == 1)
			{
				dsh->status = 2;
				free(input);
				continue;
			}
			input = rep_var(input, dsh);
			loop = split_commands(dsh, input);
			dsh->counter++;
			free(input);
		} else
		{
			loop = 0;
			free(input);
		}
	}
}

