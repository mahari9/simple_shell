#include "shell.h"

/**
 * impl_var - implement variable replacement
 * @cmd: command to be modified and replace
 *
 * Return: value on success or NULL on failure
 */
char *impl_var(char *cmd)
{
	char *name, *buffer, *value = NULL, *cmdcopy = cmd;

	if (cmd[0] == '$')
	{
		name = ++cmd;
		buffer = ma_getenv(name);
		if (buffer != NULL)
		{
			value = malloc(strlen(buffer) + 1);
			ma_strcpy(value, buffer);
			free(buffer);
			return (value);
		}
		free(buffer);
		return (update_var(cmdcopy));
	}
	return (NULL);
}

/**
 * update_var - replace and update variables
 * @cmd: command to tested
 * Return: append string or NUll on failure
 */
char *update_var(char *cmd)
{
	char *buffer, *cmdcopy = cmd;
	size_t i = 0, size = 254, verify = 0;
	pid_t pid;

	buffer = (char*)malloc(size);
	if (!buffer)
		return (NULL);
	while (*cmd)
	{
		if (cmd[0] == '$' && cmd[1] == '$')
		{
			pid = getpid();
			append_str(&buffer, NULL, pid, &i);
			cmd += 2;
			verify++;
		}
		else if (cmd[0] == '$' && cmd[1] == '?')
		{
			append_str(&buffer, NULL, status, &i);
			cmd += 2;
			verify++;
		}
		else
			buffer[i++] = *cmd++;
	}
	buffer[i] = '\0';
	if (verify)
		return (buffer);
	if (cmdcopy[0] == '$' && cmdcopy[1])
		replflag = 1;
	free(buffer);
	return (NULL);
}

/**
 * signal_catcher - catch signal (Ctrl-C) interrupt from terminating the shell
 *
 * @sign_num: an integer that contains the signal number
 *
 * Return: nothing
 */

void signal_catcher(int sign_num)
{
	write(STDOUT_FILENO, "\n$ ", 2);
	(void) sign_num;
}

