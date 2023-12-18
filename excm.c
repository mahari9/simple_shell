#include "shel.h"
/**
 * inputcommand_execute - handle execution of input external commands
 * @argv: vector arguments
 * @count: ....
 * @argus: ....
 * @envm: array of pointer to the environment variables
 * Return: 0 (Success)
 */

int inputcommand_execute(char **argv, char **argus, char *usrin, int count, char **envm)
{
	char *pth_cmnd = ma_whichpath(argv[0]);
	int stat = 0;
	pid_t pid;

	if (pth_cmnd != NULL)
	{
		pid = fork();
		if (pid == 0)
		{
			stat = execve(pth_cmnd, argv, impl_env(envm));
			if (stat == -1)
			{
				if (usrin)
					free(pth_cmnd);
				perror("execve");
				return (-1);
			}
		}
		else if (pid == -1)
		{
			if (usrin)
				free(pth_cmnd);
			perror("forking");
			return (-1);
		}
		else
		{
			return (p_process(argv, argus, count, pid));
		}
	}
	else
		stat = ma_perror(argus, count, argv, 127);
	return (stat);
}

/**
 * p_process - handle parent proccess after forking(pid = 0)
 * @argv: vector of arguments
 * argus: ....
 * count: ....
 * @pid: proccess id
 * Return: 0 (Success)
 */

int p_process(char **argv, char **argus, int count, pid_t pid)
{
	int stat;

	if (waitpid(pid, &stat, 0) == -1)
	{
		perror("waitpid");
		return (-1);
	}
	if (WIFEXITED(stat))
	{
		stat = WEXITSTATUS(stat);
		if (stat != 0)
			ma_perror(argus, count,argv, stat);
	}
	else if (WIFSIGNALED(stat))
		stat = (128 + WTERMSIG(stat));
	else
		stat = 127;
	return (stat);
}
