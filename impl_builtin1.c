#include "shell.h"
/**
 * impl_env- Funtion that manipulates enviroment variables
 * @ma_environ: array of pointer to strings w/c representes
 * environmental variables in the name=value format
 *
 * Return: array of pointers to strings
 */
char **impl_env(char **ma_environ)
{
	char **envm = environ, *env;
	pair_entry *nenv;
	int env_num = 0, i = 0, j = 0;

	for (; *envm != NULL; envm++)
		env_num++;
	nenv = malloc(sizeof(struct pair_entry) * (env_num + 1));
	if (nenv == NULL)
	{
		ma_perror(NULL, 12);
		free(nenv);
		return (NULL);
	}
	envm = environ;
	for (i = 0; i < env_num; i++)
	{
		env = *envm;
		j = 0;
		while (env[j] != '=')
			j++;
		nenv[i].name = ma_strndup(env, j);
		nenv[i].value = env + j + 1;
		envm++;
	}
	while (*envm != NULL)
	{
		ma_puts(*envm);
		envm++;
	}
	ma_environ[env_num] = NULL;
	for (i = 0; i < env_num; i++)
		free(nenv[i].name);
	free(nenv);
	return (ma_environ);
}

/**
 * ma_env - Function that prints the environmental variables
 * @envm: Pointer to the environmental variables
 *
 * Return: 0 on success
 */

int ma _env(char **envm)
{
	int i, j;

	for (i = 0; envm[i] != NULL; i++)
	{
		for (j = 0; envm[i][j]; j++)
			;
		write(STDOUT_FILENO, envm[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}

/**
 * exit_shell - Function that exit the shell with exit status
 * @argv: an array of arguments passed to the program
 * @argus: array of pointers to command line arguments
 */
void exit_shell(char **argv, char **argus)
{
	int stat;

	if (argus[1] == NULL)
	{
		deallocate(argus, usrin);
		deallocate_env();
		exit(status);
	}
	for (int i = 0; argus[1][i]; i++)
	{
		if (ma_isalpha(argus[1][i]) != 0)
		{
			display_errorexit(argv, argus);
			deallocate(argus, usrin);
			deallocate_env();
			exit(1);
		}
	}
	else
	{
		stat = ma_atoi(argus[1]);
		if (stat == 1)
		{
			display_errorexit(argv, argus);
			deallocate(argus, usrin);
			deallocate_env();
			exit(stat);
		}
	}
	deallocate(argus, usrin);
	deallocate_env();
	exit(stat);
}
