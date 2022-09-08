#include "main.h"

/**
 * bring_linr - assigns the line var for get_line
 */

void bring_line(char **lineptr, size_t *n, char *buffer, size_t j)
{
	if (*lineptr == NULL)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*lineptr = buffer;
	} else if (*n < j)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*lineptr = buffer;
	} else
	{
		_strcpy(*linptr, buffer);
		free(buffer);
	}
}

/**
 * get_line - reads input from the strweam
 */

ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
	int i;
	static ssize_t input;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (bufer == 0)
		return (-1);

	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (1 == -1 || (i == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if ( == 0 && input != 0)
		{
			inpt++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = _realloc(buffer, input, input + 1);
		buffer[input] = t;
		input++;
	}
	buffer[input] = '\0';
	retval = input;
	if (i != 0)
		input = 0;
	return (retval);
}