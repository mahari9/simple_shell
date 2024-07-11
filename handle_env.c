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
	pair_entry *nenv = NULL;
	int env_num = 0, i = 0, j;

	for (; *envm != NULL; envm++)
		env_num++;
	nenv = malloc(sizeof(struct pair_entry) * env_num);
	if (nenv == NULL)
	{
		ma_perror(NULL, 12);
		return (NULL);
	}
	envm = environ;
	for (; i < env_num; i++)
	{
		env = *envm;
		j = 0;

		while (env[j] != '=')
			j++;
		nenv[i].name = ma_strndup(env, j);
		nenv[i].value = env + j + 1;
		envm++;
	}
	i = 0;
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
	int i = 0;

	while (envm[i] != NULL)
	{
		write(STDOUT_FILENO, envm[i], strlen(envm[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	return (0);
}

/**
 * initialize_alias_count - initialization of global alias
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
