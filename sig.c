#include "shel.h"

/**
 * signal_catcher - catch signal (Ctrl-C) interrupt from terminating the shell
 *
 * @sign_num: an integer that contains the signal number
 *
 * Return: nothing
 */

void signal_catcher(int sign_num)
{
	if (sign_num == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		display_prompt();
	}
}

/**
 * setup_signal_catcher - setup signal catcher in the system
 *
 * Return: 0 success, -1 failure
 */
int setup_signal_catcher(void)
{
	if (signal(SIGINT, signal_catcher) == SIG_ERR)
	{
		write(STDOUT_FILENO, "sig_num is invalid\n", 19);
		return (-1);
	}
	return (0);
}
