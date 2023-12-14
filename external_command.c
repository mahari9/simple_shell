#include "shell.h"
/**
 * inputcommand_execute - handle execution of input external commands
 * @argv: vector arguments
 * @argus: parsed command to be executed
 * @envm: array of pointer to the environment variables
 * Return: 0 (Success)
 */

int inputcommand_execute(char **argv, char **argus, char **envm)
{
	char *pth_cmnd = ma_whichpath(argv[0]);
	int stat = 0;
	pid_t pid;

	if (pth_cmnd != NULL)
	{
		if (pid == 0)
		{
			stat = execve(pth_cmnd, argv, impl_env(envm));
			if (stat == -1)
			{
				if (source)
					free(pth_cmnd);
				perror("execve");
				return (-1);
			}
		}
		else if (pid == -1)
		{
			if (stat)
				free(pth_cmnd);
			perror("forking");
			return (-1);
		}
		else
		{
			if (source)
				free(pth_cmnd);
			return (p_process(argv, argus, pid));
		}
	}
	else
		stat = ma_perror(argv, argus, 127);
	return (stat);
}

/**
 * p_process - handle parent proccess after forking(pid = 0)
 * @argv: vector of arguments
 * @argus: parsed command to be executed
 * @pid: proccess id
 * Return: 0 (Success)
 */

int p_process(char **argv, char **argus, pid_t pid)
{
	int stat;

	if (waitpid(pid, &stat, 0) == -1)
	{
		perror("waitpid");
		return (-1);
	}
	if (WIFEXITED(stat))
	{
		status = WEXITSTATUS(stat);
		if (status != 0)
			ma_perror(argv, argus, status);
	}
	else if (WIFSIGNALED(stat))
		status = (128 + WTERMSIG(stat));
	else
		status = 127;
	return (status);
}
