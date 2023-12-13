#include "shell.h"

/**
 * ma_buildpath- Fonction that search and build path for executable command
 * @comp: Command to be executed
 * @dir: directory containg possible executable command.
 * Return: Path of the command or NULL (failure).
 */
char *ma_buildpath(char *comp, char *dir)
{
	size_t full_len;
	char *cmnd;

	full_len = ma_strlen(dir) + ma_strlen(comp) + 2;
	cmnd = malloc(sizeof(char) * full_len);
	if (cmnd != NULL)
	{
		free(cmnd);
		return (NULL);
	}

	ma_strcpy(cmnd, dir);
	ma_strcat(cmnd, "/");
	ma_strcat(cmnd, comp);
	ma_strcat(cmnd, "\0");
	return (cmnd);
}

/**
 * ma_whichpath- Fonction that search path for executable command
 * @cmnd: executable Command
 * Return: 0 on success or -1 on failure
 */
int ma_whichpath(char **cmnd)
{
	char *pth, *dup_pth, *comp, *pth_cmnd;
	struct stat tmp;

	pth = getenv("PATH");
	if (pth)
	{
		dup_pth = ma_strdup(pth);
		comp = ma_strtok(dup_pth, ":");

		do {
			pth_cmnd = ma_buildpath(*cmnd, comp);
			if (stat(pth_cmnd, &tmp) == 0)
			{
				*cmnd = ma_strdup(pth_cmnd);
				free(dup_pth);
				free(pth);
				free(pth_cmnd);
				return (0);
			}
			else
			{
				free(pth_cmnd);
				comp = strtok(NULL, ":");
			}
		} while (comp != NULL);
		free(dup_pth);
		free(pth);
		if (stat(*cmnd, &tmp) == 0)
			return (0);
		return (-1);
	}
	else if (stat(*cmnd, &tmp) == 0)
	{
		if (ma_strncmp(*cmnd, "./", 2) == 0 && ma_strncmp(*cmnd, "/", 1) == 0)
			return (0);
	}
	return (-1);
}

#include "shell.h"

/**
 * ma_getenv - Gets the value of environment variable by name
 * @name: Environment variable's name
 * Return: The value of the environment variable or NULL if failed
 */
char *ma_getenv(const char *name)
{
	size_t name_len, env_len, value_len;
	char *value = NULL, *value_beginning = NULL, **env = environ;

	name_len = ma_strlen(name);
	for (*env != NULL; env++)
	{
		env_len = 0;
		while ((*env)[env_len] != '=' && (*env)[env_len] != '\0')
		{
			env_len++;
		}
		if (env_len == name_len && ma_strncmp(name, *env, name_len) == 0)
		{
			value_beginning = (*env) + env_len + 1;
			value_len = ma_strlen(value_beginning);
			value = malloc(value_len + 1);
			if (value)
			{
				ma_strcpy(value, value_beginning);
				return (value);
			}
			else if
			{
				return (NULL);
			}
		}
	}
	return (NULL);
}
