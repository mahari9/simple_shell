#include "shell.h"

/**
 * search_alias - Finds an alias by it's name from alias's list
 * @nam: alias's name to be searched
 * @row: pointer to store the index of the found alias
 * Return: value of the alias or NULL if not found
 */
char *search_alias(char *nam, int *row)
{
	int j;
	char *al_valu, *found;

	for (j = 0; G_alias.aliases[j].name != NULL; j++)
	{
		if (ma_strcmp(nam, G_alias.aliases[j].name) == 0)
		{
			if (row != NULL)
				*row = j;
			al_valu = G_alias.aliases[j].value;
			found = search_alias(G_alias.aliases[j].value, row);
			if (found)
				return (found);
			else
				return (al_valu);
		}
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
	char *aliaslis = NULL;

	len = ma_strlen(G_alias.aliases[r].name)
	+ ma_strlen(G_alias.aliases[r].value);
	aliaslis = malloc(sizeof(char) * (len + 5));

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
	if (ar_count == 0)
	{
		for (i = 0; i < G_alias.a_count; i++)
			print_alias(i);
		return;
	}
	for (; col < ar_count; n++, col++)
	{
		equal = ma_strchr(argus[n], '=');
		if (!equal)
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
