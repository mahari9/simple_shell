#include "shell.h"

/**
 * ma_buildpath- Function that search and build path for executable command
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
 * ma_whichpath- Function that search path for executable command
 * @cmnd: executable Command
 * Return: path to executable cmnd or NULL
 */
char *ma_whichpath(char *cmnd)
{
	char *pth, *dup_pth, *comp, *pth_cmnd;
	struct stat tmp;

	pth = getenv("PATH");
	if (pth)
	{
		dup_pth = ma_strdup(pth);
		comp = ma_strtok(dup_pth, ":");

		do {
			pth_cmnd = ma_buildpath(cmnd, comp);
			if (stat(pth_cmnd, &tmp) == 0)
			{
				cmnd = ma_strdup(pth_cmnd);
				free(dup_pth);
				free(pth);
				return (pth_cmnd);
			}
			else
			{
				free(pth_cmnd);
				comp = strtok(NULL, ":");
			}
		} while (comp != NULL);
		free(dup_pth);
		free(pth);
		if (stat(cmnd, &tmp) == 0)
			return (cmnd);
		return (NULL);
	}
	else if (stat(cmnd, &tmp) == 0)
	{
		if (ma_strncmp(cmnd, "./", 2) == 0 && ma_strncmp(cmnd, "/", 1) == 0)
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
	char **envm = environ, *value, *value_start;
	size_t value_length;

	if (!name || !environ)
		return (NULL);
	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; name[j] != '\0' && name[j] == envm[i][j]; j++)
		if (name[j] == '\0' && envm[i][j] == '=')
		{
			value_start = &envm[i][j + 1];
			value_length = ma_strlen(value_start);

			value = malloc(value_length + 1);

			if (value)
			{
				ma_strcpy(value, value_start);
				return (value);
			}
		}
	}
	return (NULL);
}
