#include "shell.h"

/**
 * external_command - Function that handles external commands execution
 * @argu: Arroy of pointers to executable command
 * @usrin: input by user
 * @argv: array of arguments passed to function
 * @envm: pointer to the environment variables
 * Return: 0 (Success)
 */
int external_command(char **argu, char *usrin, char **argv, char **envm)
{
	pid_t pid;

	if (*argu == NULL)
		return (EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
	{
		perror("forking");
		return (-1);
	}
	if (pid == 0)
	{
		ma_whichpath(argu);
		if (access(argu[0], X_OK) != 0)
		{
			ma_perror(argv, argu, 126);
			deallocate(argu, usrin);
			exit(126);
		}
		if (execve(*argu, argu, impl_env(envm)) == -1)
		{
			ma_perror(argv, argu, 127);
			deallocate(argu, usrin);
			perror("execve");
			exit(127);
		}
		else
		{
			return (p_process(pid, argu, argv));
		}
	}
}

/**
 * p_process- handles parent proccess after fork
 * @argu: array of pointers to executable command
 * @argv: array of arguments passed to function
 * @pid: proccess id
 * Return: 0 (Success)
 */

int p_process(pid_t pid, char **argu, char **argv)
{
	int wstatus;

	if (waitpid(-1, &wstatus, 0) == -1)
	{
		perror("waitpid");
		return (-1);
	}
	if (WIFEXITED(wstatus))
	{
		status = WEXITSTATUS(wstatus);
		if (status != 0)
			ma_perror(argv, argu, status);
		return (status);
	}
	else if (WIFSIGNALED(wstatus))
		return (128 + WTERMSIG(wstatus));
	else if
		return (127);
	return (0);
}
