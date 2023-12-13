#include "main.h"

/**
 * create_env - Function that creates strings w/c are environmental variables
 * @name: name of environmental variable
 * @value: value of environmental
 *
 * Return: created env
 */
char *create_env(char *name, char *value)
{
	char *env_v;
	int len_name, len_value, len;

	len_name = ma_strlen(name);
	len_value = ma_strlen(value);
	len = len_name + len_value + 2;
	env_v = malloc(sizeof(char) * (len));
	if (env_v == NULL)
		return (error_handler(NULL, 50));
	ma_strcpy(env_v, name);
	ma_strcat(env_v, "=");
	ma_strcat(env_v, value);
	ma_strcat(env_v, "\0");

	return (env_v);
}

/**
 * ma_setenv - Function that modify or add an environment variable
 * @name: name of environmental variable
 * @value: value of enviromental variable
 *
 * Return: 0 on success, -1 on failure
 */
int ma_setenv(char *name, char *value)
{
	char **env, *env_var = NULL, **mod_environ = NULL;
	int i, j = 0;

	if ((ma_strchr(name, '=') != NULL) || (ma_strlen(name) == 0))
		return (error_handler(NULL, 22));
	track_address(env_var);
	env_var = create_env(name, value);
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
	mod_environ = malloc(sizeof(char *) * (j + 2));
	if (mod_environ == NULL)
		return (ma_perror(NULL, NULL 12));
	track_address(mod_environ);
	for (i = 0; environ[i]; i++)
		mod_environ[i] = environ[i];
	mod_environ[i] = env_var;
	mod_environ[i + 1] = NULL;
	environ = mod_environ;
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
		return (error_handler(NULL, 22));
	/* Iterate through the environ and remove if it exists */
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
 * Return: 1 on success else 0
 */
int track_address(void *p)
{
	char msg[] = "env is on maximum limit\n";

	if (num_p < 50)
	{
		env_n[num_p++] = p;
		return (1);
	}
	else
		WRT(msg);
	return (0);
}
