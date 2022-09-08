#include "main.h"

/**
 * swap_char - swap | and & for non-printed chars
 */

char *swap_char(char *input, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; input[i]; i++)
		{
			if (input[i] == '|')
			{
				if (input[i + 1] != '|')
					input[i] = 16;
				else
					i++;
			}
			if (input[i] == '&')
			{
				if (input[i + 1] != '&')
					input[i] = 12;
				else
					i++;
			}
		}
	} else
		for (i = 0; input[i]; i++)
		{
			input[i] = (input[i] == 16 ? '|' : input[i]);
			input[i] = (input[i] == 12 ? '&' : input[i]);
		}

	return (input);
}

/**
 * add_nodes - adds separators and commandlines in the lists
 */

void add_nodes(sep_list **head_s, line_list **head_l, char *input)
{
	int i;
	char *line;

	input = swap_char(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			add_sep_node_end(head_s, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			add_sep_node_end(head_s, input[i]);
			i++;
		}
	}

	line = _strtok(input, ";|&");
	do {
		line = swap_char(line, 1);
		add_line_node_end(head_l, line);
		line = _strtok(NULL, ";|&")
	} while (line != NULL);
}

/**
 * go_next - go to the next command line stored
 */

void go_next(sep_list **list_s, line_list **list_l, data_sh *dsh)
{
	int loop_sep;
	sep_list *ls_s;
	line_list *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (dsh->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_s = 0;
			if (ls_s->separator == '|')
			{
				ls_l = ls_l->next;
				ls_s = ls->separator;
			}
		} else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '&')
			{
				ls_l = ls_l->next;
				ls_s = ls_s->next;
			}
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}
	*list_s = ls_s;
	*list_l = ls_l;

}

/**
 * split_commands - splits command lines according to separators
 * ;, | and & and executes them
 */

int split_command(data_sh *dsh, char *input)
{
	sep_list *head_s, *list_s;
	line_list *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	add_nodes(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		dsh->input = list_l->line;
		dsh->args = split_line(dsh->input);
		loop = exec_line(dsh);
		free(dsh->args);

		if (loop == 0)
			break;

		if (list_l != NULL)
			list_l = list_l->next;
	}

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * split_line - tokenizes the input string
 */

char **split_line(char *input)
{
	size_t i, bsize;
	char **tokens;
	char *token;

	bsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(input, TOK_DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOK_BUFSIZE;
			tokens = _realloc(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
		tokens[i] = token;
	}
	return (tokens);
}



