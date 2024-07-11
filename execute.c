#include "shell.h"

/**
 * p_process - handle parent proccess after forking(pid = 0)
 * @argv: vector of arguments
 * @pid: proccess id
 * Return: 0 (Success)
 */

int p_process(pid_t pid, char **argv)
{
	int status;

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		return (-1);
	}
	if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
		if (exit_status != 0)
			ma_perror(argv, exit_status);
	}
	else if (WIFSIGNALED(status))
		exit_status = (128 + WTERMSIG(status));
	else
		exit_status = 127;
	return (exit_status);
}


/**
 * inputcommand_execute - handle execution of input external commands
 * @argv: vector arguments
 * @envm: array of pointer to the environment variables
 * Return: 0 (Success)
 */

int inputcommand_execute(char **argv, char **envm)
{
	char *pth_cmnd = ma_whichpath(argv[0]);
	int status = 0;
	pid_t pid;

	if (pth_cmnd != NULL)
	{
		pid = fork();
		if (pid == 0)
		{
			status = execve(pth_cmnd, argv, impl_env(envm));
			if (status == -1)
			{
				if (source)
					free(pth_cmnd);
				perror("execve");
				return (-1);
			}
		}
		else if (pid == -1)
		{
			if (source)
				free(pth_cmnd);
			perror("fork");
			return (-1);
		}
		else
		{
			if (source)
				free(pth_cmnd);
			return (p_process(pid, argv));
		}
	}
	else
		status = ma_perror(argv, 127);
	return (status);
}

/**
 * execute_builtin - Handles predefined built-in commands
 * @argus: Array pointers to the arguments passed to the program
 *
 * Return: 0 (Success)
 */

int execute_builtin(char **argus)
{
	if (ma_strcmp(argus[0], "alias") == 0)
	{
		ma_alias(argus);
		return (0);
	}
	if (ma_strcmp(argus[0], "cd") == 0)
	{
		ma_cd(argus[1]);
		return (0);
	}
	else if (ma_strcmp(argus[0], "env") == 0)
		return (ma_env(environ));
	else if (ma_strcmp(argus[0], "exit") == 0)
		return (exit_shell(argus));
	else if (ma_strcmp(argus[0], "setenv") == 0)
	{
		if ((argus[1] == NULL) || (argus[2] == NULL) || (argus[3] != NULL))
		{
			write(2, "usage: setenv VARIABLE VALUE\n", 29);
			return (-1);
		}
		return (ma_setenv(argus[1], argus[2]));
	}
	else if (ma_strcmp(argus[0], "unsetenv") == 0)
	{
		if ((argus[1] == NULL) || (argus[2] != NULL))
		{
			write(2, "usage: unsetenv VARIABLE\n", 25);
			return (-1);
		}
		return (ma_unsetenv(argus[1]));
	}
	return (1);
}


/**
 * handle_commands - Function that handles execution of different commands
 * @argus: Array of pointers to command line arguments passed to function
 * Return: 0 on success
 */
int handle_commands(char **argus)
{
	char **envm = environ, *found;
	int bltin, i;

	for (i = 0; argus[i] != NULL; i++)
	{
		found = search_alias(argus[i], NULL);
		if (found && (ma_strcmp(argus[0], "alias") != 0))
		{
			free(argus[i]);
			argus[i] = ma_strdup(found);
		}
	}
	if (argus && argus[0])
	{
		bltin = execute_builtin(argus);
		if (bltin != 1)
			return (bltin);
		else
			return (inputcommand_execute(argus, envm));
	}
	else
		return (0);
}
