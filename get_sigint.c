#include "main.h"

/**
 * get_sigint - handles the ctrl + c call in promt
 * @sig: signal handler
 */

void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
