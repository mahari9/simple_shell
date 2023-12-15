#include "shell.h"

/**
 * search_alias - Finds an alias by it's name from alias's list
 * @nam: alias's name to be searched
 * @row: pointer to store the index of the found alias
 * Return: value of the alias or NULL if not found
 */
char *search_alias(char *nam, int *row)
{
	int j, found;
	char *al_valu;

	while (1)
	{
		found = 0;
		for (j = 0; G_alias.aliases[j].name != NULL; j++)
		{
			if (ma_strcmp(nam, G_alias.aliases[j].name) == 0)
			{
				if (row != NULL)
					*row = j;

				al_valu = G_alias.aliases[j].value;
				nam = al_valu;
				found = 1;
				break;
			}
		}
		if (!found)
			return (NULL);
	}
	return (NULL);
}

/**
 * define_alias - Adds a new alias if it doesn't exist or
 * updates an existing one
 * @al_name: alias name to be added or updated
 * @al_value: value of alias to be added
 * Retrun: Nothing
 */
void define_alias(char *al_name, char *al_value)
{
	int row;
	char *found;

	G_alias.a_count = 0;
	found = search_alias(al_name, &row);
	if (found)
		G_alias.aliases[row].value = al_value;
	else
	{
		G_alias.aliases[G_alias.a_count].name = al_name;
		G_alias.aliases[G_alias.a_count].value = al_value;
		G_alias.a_count++;
	}
}

/**
 * print_alias - Prints a list of all aliases,
 * one per line, in the form name='value'
 * @r: nth alias
 */
void print_alias(int r)
{
	int len;
	char *aliaslis;

	aliaslis = NULL;

	len = ma_strlen(G_alias.aliases[r].name)
	+ ma_strlen(G_alias.aliases[r].value);
	aliaslis = malloc(sizeof(char) * (len + 5));
	if (aliaslis == NULL)
	{
		ma_perror(NULL, 12);
		return;
	}
	ma_strcpy(aliaslis, G_alias.aliases[r].name);
	ma_strcat(aliaslis, "='");
	ma_strcat(aliaslis, G_alias.aliases[r].value);
	ma_strcat(aliaslis, "'\n");
	write(STDOUT_FILENO, aliaslis, ma_strlen(aliaslis));
	free(aliaslis);
}

/**
 * ma_alias - Function that implements the built-in alias command
 * @argus: array of arguments passed to program
 * Return: 0 on success
 */
void ma_alias(char **argus)
{
	int i, n = 1, col = 0, row = 0, namelen, ar_count = -1;
	char *namelist[MAXALS], *equal, *valuebegin, *valuelist[MAXALS];

	for (i = 0; argus[i]; i++)
		ar_count++;
	if (!ar_count)
	{
		for (i = 0; i < G_alias.a_count; i++)
			print_alias(i);
	}
	for (; col < ar_count; n++, col++)
	{
		equal = ma_strchr(argus[n], '=');
		if (equal == NULL)
		{
			for (i = 0; i <= G_alias.a_count; i++)
				if ((G_alias.aliases[i].name)
						&& (ma_strcmp(argus[n], G_alias.aliases[i].name) == 0))
				{
					print_alias(i);
					break;
				}
		}
		else
		{
			namelen = equal - argus[n];
			valuebegin = argus[n] + (namelen + 1);
			namelist[row] = ma_strndup(argus[n], namelen);
			track_address(namelist[row]);
			valuelist[row] = ma_strdup(valuebegin);
			track_address(valuelist[row]);
			define_alias(namelist[row], valuelist[row]);
			row++;
		}
	}
	namelist[row] = NULL;
	valuelist[row] = NULL;
}


/**
 * ma_cd - change the current directory of the process
 * @argus: Array of pointers to the arguments
 * Return: 0 on success, -1 on failure
 */
int ma_cd(char **argus)
{
	char *cwd = NULL, *home = NULL, *prev_dir = NULL,
	     *dir = argus[1], *old_dir = getcwd(NULL, 0);
	int value;

	track_address(old_dir);
	cwd = getcwd(NULL, 0);
	track_address(cwd);
	if (!argus[1])
	{
		home = ma_getenv("HOME");
		track_address(home);
		if (!home)
			value = chdir((home = ma_getenv("PWD")) ? home : "/");
		else
			value = chdir(home);
	}
	else if (ma_strcmp(dir, "-") == 0)
	{
		prev_dir = ma_getenv("OLDPWD");
		track_address(prev_dir);
		if (!prev_dir)
		{
			write(1, cwd, ma_strlen(cwd));
			write(1, "\n", 1);
			return (1);
		}
		write(1, prev_dir, ma_strlen(prev_dir));
		write(1, "\n", 1);
		value = chdir((prev_dir = ma_getenv("OLDPWD=")) ? prev_dir : "/");
	}
	else
	{
		if (chdir(dir) != 0)
			ma_perror_cd(argus, 3);
		return (-1);
	}
	ma_setenv("OLDPWD", old_dir);
	ma_setenv("PWD", cwd);
	return (value);
}
