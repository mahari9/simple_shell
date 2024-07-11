#include "shell.h"
/**
 * ma_whichpath- Function that search path for executable command
 *@cmnd: Command to be executed
 * Return: path to executable cmnd or NULL
 */
char *ma_whichpath(char *cmnd)
{
	char *pth = NULL, *dup_pth = NULL, *pth_cmnd, *comp;
	struct stat tmp;

	pth = ma_getenv("PATH");
	if (pth)
	{
		dup_pth = ma_strdup(pth);
		comp = strtok(dup_pth, ":");

		while (comp != NULL)
		{
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
				comp = strtok(NULL, ":");
			}
		}
		if (dup_pth)
			free(dup_pth);
		free(pth);

		if (stat(cmnd, &tmp) == 0)
			return (cmnd);
		return (NULL);
	}
	else if ((no_pth == 1) && (stat(cmnd, &tmp) == 0))
		if ((check_abspth(cmnd)))
			return (cmnd);
	return (NULL);
}

/**
 * ma_buildpath- Function that search and build path for executable command
 * @cmnd: Command to be executed
 * @dir: directory containg possible executable command.
 * Return: Path of the command or NULL (failure).
 */

char *ma_buildpath(char *cmnd, char *dir)
{
	int len_cmnd, len_dir;
	char *pth_cmnd;

	len_cmnd = ma_strlen(cmnd);
	len_dir = ma_strlen(dir);
	pth_cmnd = malloc(len_cmnd + len_dir + 2);
	if (pth_cmnd)
	{
		ma_strcpy(pth_cmnd, dir);
		ma_strcat(pth_cmnd, "/");
		ma_strcat(pth_cmnd, cmnd);
		ma_strcat(pth_cmnd, "\0");
	}
	return (pth_cmnd);
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
		{
			/*compare chars until they differ or name[j] is '\0'*/
		}
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

/**
 * check_abspth - Function that checks whether the provided path is absolute
 * @dir: dirctory which contains the path
 *
 * Return: 1 if absolute or 0 if not
 */
int check_abspth(const char *dir)
{
	char *forward_slash;

	forward_slash = ma_strchr(dir, '/');
	if (forward_slash != NULL && forward_slash == dir)
		return (1);
	else
		return (0);
}
