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

int ma_env(char **envm)
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
 */
void exit_shell(char **argv)
{
	int stat, i;

	if (argv[1] == NULL)
	{
		sweep_all(argv);
		exit(status);
	}
	for (i = 0; argv[1][i]; i++)
	{
		if (ma_isalpha(argv[1][i]) != 0)
		{
			display_errorexit(argv);
			sweep_all(argv);
			exit(1);
		}
		else
		{
			stat = ma_atoi(argv[1]);
			if (stat == 1)
			{
				display_errorexit(argv);
				sweep_all(argv);
				exit(stat);
			}
		}
	}
	sweep_all(argv);
	exit(stat);
}

/**
 * initialize_alias_count- initialization of global alias
 * list of aliases and alias_count
 */
void initialize_alias_count(void)
{
	int i;

	for (i = 0; i < MAXALS; ++i)
	{
		G_alias.aliases[i].name = NULL;
		G_alias.aliases[i].value = NULL;
	}
	G_alias.a_count = 0;
}
