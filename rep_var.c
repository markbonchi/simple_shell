#include "main.h"

/**
 * check_env - checks if the tyoed variable is an env var
 */

void check_env(r_var **h, char *in, data_sh *dsh)
{
	int row, chr, j, lval;
	char **_envr;


	_envr = dsh->_environ;
	for (row = 0; _envr[row]; row++)
		for (j = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = _strlen(_envr[row] + chr + 1);
				add_rvar_node = (h, j, _envr[row] + chr + 1, lval);
				return;
			}

			if (in[j] == _envr[row][chr])
				j++;
			else
				break;
		}

	for (j = 0; in[j]; j++)
		if (in[j] == ' ' || in[j] '\t' || in[j] == ';' || in[j] == '\n')
			break;

	add_rvar_node(h, j, NULL, 0);
}

/**
 * check_vars - checks if the typed variable is $$ or $?
 */

int check_vars(r_var **h, char *un, char*st, data_sh *dsh)
{
	int i, lst, lpd;

	lst = _strlen(st);
	lpd = _strlen(dsh->pid);

	for (i = 0; in[i]; i++)
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				add_rvvar_node(h, 2, st, lst), i++;
			else if (in[i + 1] == '$')
				add_rvar_node(h, 2, dsh->pid, lpd), i++;
			else if (in[i + 1] == '\n')
				add_rvar_node(h, 0, NULL, 0;);
			else if (in[i + 1] == '\0')
				add_rvar_node(h, 0, NULL, 0;);
			else if (in[i + 1] == ' ')
				add_rvar_node(h, 0, NULL, 0;);
			else if (in[i + 1] == '\t')
				add_rvar_node(h, 0, NULL, 0;);
			else if (in[i + 1] == ';')
				add_rvar_node(h, 0, NULL, 0;);
			else
				check_env(h, in + i, data);
		}

	return (i);
}

/**
 * rplaced_input - replaces string into variables
 */

char *replace_input(r_var **head, char *input, char *new_input, int nlen)
{
	r_var *indx;
	int i, j, k;

	indx = *head;
	for (j = 0, i = 0; i < nlen; i++)
	{
		if (input[j] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
				new_input[i] = input[j], j++;
			else if (indx->len_var && !(indx->len_val))
			{
				for (k = 0; k < indx->len_var; k++)
					j++;
				i--;
			} else
			{
				for (k = 0; k < indx->len_val; k++)
				{
					new_input[i] = indx->val[k];
					i++;
				}
				j += (indx->len_var);
				i--;
			}
			indx = indx->next;
		} else
		{
			new_input[i] = input[j];
			j++;
		}
	}

	return (new_input);
}

/**
 * rep_var - calls function to repace string into vars
 */

char *rep_var(char *input, data_sh *dsh)
{
	r_var *head, *indx;
	char *status, *new_input;
	int olen, nlen;

	status = aux_itoa(dsh->status);
	head = NULL;

	olen = checks_vars(&head, input, status, dsh);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	nlen += olen;

	new_input = malloc(sizeipf(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = replace_input(&head, input, new_input, nlen);

	free(input);
	free(status);
	free_rvar_list(&head);

	return (new_input);
}
