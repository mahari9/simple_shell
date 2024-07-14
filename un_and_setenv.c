#include "shell.h"

/**
 * ma_setenv - Function that modify or add an environment variable
 * @name: name of environmental variable
 * @value: value of enviromental variable
 *
 * Return: 0 on success
 */
int ma_setenv(char *name, char *value)
{
	char **env, *env_var = NULL, **set_environ = NULL;
	int i, j = 0;

	if ((ma_strchr(name, '=') != NULL) || (ma_strlen(name) == 0))
		return (ma_perror(NULL, 22));
	env_var = malloc(ma_strlen(name) + ma_strlen(value) + 2);
	if (env_var == NULL)
		return (ma_perror(NULL, 12));
	track_address(env_var);
	ma_strcpy(env_var, name);
	ma_strcat(env_var, "=");
	ma_strcat(env_var, value);
	for (env = environ; *env; env++)
	{
		if (ma_strncmp(*env, name, ma_strlen(name)) == 0 &&
		    (*env)[ma_strlen(name)] == '=')
		{
			*env = env_var;
			return (0);
		}
	}
	for (env = environ; *env; env++)
		j++;
	set_environ = malloc((j + 2) * sizeof(char *));
	if (set_environ == NULL)
		return (ma_perror(NULL, 12));
	track_address(set_environ);
	for (i = 0; environ[i]; i++)
		set_environ[i] = environ[i];
	set_environ[i] = env_var;
	set_environ[i + 1] = NULL;
	environ = set_environ;
	return (0);
}

/**
 * ma_unsetenv - Function that removes/delete environmental variable
 * @name: name of environment variable
 *
 * Return: 0 on success
 */
int ma_unsetenv(char *name)
{
	char **env, **del;

	if ((ma_strchr(name, '=') != NULL) || (ma_strlen(name) == 0))
		return (ma_perror(NULL, 22));
	for (env = environ; *env; env++)
	{
		if (ma_strncmp(*env, name, ma_strlen(name)) == 0 &&
				(*env)[ma_strlen(name)] == '=')
		{
			del = env;
			while (*del)
			{
				*del = *(del + 1);
				++del;
			}
			return (0);
		}
	}

	return (0);
}

/**
 * track_address - Add address of given pointer to an array
 * @p: pointer of which it's address will stored in the array env_n
 * Return: Nothing
 */
void track_address(void *p)
{
	char msg[] = "env is on maximum limit\n";

	if (num_p < 150)
	{
		env_n[num_p++] = p;
	}
	else
		WRT(msg);
}
