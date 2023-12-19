#include "shell.h"

/**
 * ma_buildpath- Function that search and build path for executable command
 * @comp: Command to be executed
 * @dir: directory containg possible executable command.
 * Return: Path of the command or NULL (failure).
 */
char *ma_buildpath(char *comp, char *dir)
{
	int full_len;
	char *pth_cmnd;

	full_len = ma_strlen(dir) + ma_strlen(comp) + 2;
	pth_cmnd = malloc(full_len);
	if (pth_cmnd)
	{
		ma_strcpy(pth_cmnd, dir);
		ma_strcat(pth_cmnd, "/");
		ma_strcat(pth_cmnd, comp);
		ma_strcat(pth_cmnd, "\0");
	}
	return (pth_cmnd);
}

/**
 * ma_whichpath- Function that search path for executable command
 * @cmnd: executable Command
 * Return: path to executable cmnd or NULL
 */
char *ma_whichpath(char *cmnd)
{
	char *pth = NULL, *dup_pth = NULL, *comp, *pth_cmnd;
	struct stat tmp;

	pth = ma_getenv("PATH");
	if (pth)
	{
		dup_pth = ma_strdup(pth);
		comp = ma_strtok(dup_pth, ":");

		do {
			pth_cmnd = ma_buildpath(cmnd, comp);
			if (stat(pth_cmnd, &tmp) == 0)
			{
				if (dup_pth)
					free(dup_pth);
				free(pth);
				source = 1;
				return (pth_cmnd);
			}
			else
			{
				if (pth_cmnd)
					free(pth_cmnd);
				comp = ma_strtok(NULL, ":");
			}
		} while (comp != NULL);
		if (dup_pth)
			free(dup_pth);
		free(pth);
		if (stat(cmnd, &tmp) == 0)
			return (cmnd);
		return (NULL);
	}
	else if ((no_pth == 1) && stat(cmnd, &tmp) == 0)
	{
		if (ma_strncmp(cmnd, "/", 1) == 0)
			return (cmnd);
	}
	return (NULL);
}

/**
 * ma_getenv - Gets the value of environment variable by name
 * @name: Environment variable's name
 * Return: The value of the environment variable or NULL if failed
 */
char *ma_getenv(const char *name)
{
	int i, j;
	char **envm = environ, *value, *value_begin;
	size_t value_len;

	if (!name || !environ)
		return (NULL);
	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; name[j] != '\0' && name[j] == envm[i][j]; j++)
		if (name[j] == '\0' && envm[i][j] == '=')
		{
			value_begin = &envm[i][j + 1];
			value_len = ma_strlen(value_begin);

			value = malloc(value_len + 1);

			if (value)
			{
				ma_strcpy(value, value_begin);
				return (value);
			}
		}
	}
	return (NULL);
}
