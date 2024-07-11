#include "shell.h"

/**
 * ma_strtok - custom strtok function using a while loop
 * @usri: user input to be separated into strings
 * @separ: the separator (delimiter)
 *
 * Return: separated string
 */
char *ma_strtok(char *usri, const char *separ)
{
	static char *str;
	char *str_copy = NULL;

	if (usri != NULL)
		str = usri;
	while (*str != '\0')
	{
		int i;

		for (i = 0; separ[i] != '\0'; i++)
		{
			if (*str == separ[i])
				break;
		}
		if (separ[i] == '\0')
			break;
		str++;
	}
	str_copy = str;
	if (*str_copy == '\0')
		return (NULL);
	while (*str != '\0')
	{
		int i;

		for (i = 0; separ[i] != '\0'; i++)
		{
			if (*str == separ[i])
			{
				*str = '\0';
				str++;
				return (str_copy);
			}
		}
		str++;
	}
	return (str_copy);
}

/**
 * ma_strtok_r - function that tokenize line into  string on muilt thread safe
 * @str: line to be split into tokens of strings
 * @delim: the delimiter
 * @saveptr: adress of str for next token
 * Return: token of string
*/

char *ma_strtok_r(char *str, const char *delim, char **saveptr)
{
	char *tkn;

	if (str != NULL)
		*saveptr = str;

	while (**saveptr != '\0' && ma_strchr(delim, **saveptr) != NULL)
		(*saveptr)++;

	if (**saveptr == '\0')
		return (NULL);

	tkn = *saveptr;
	while (**saveptr != '\0' && ma_strchr(delim, **saveptr) == NULL)
		(*saveptr)++;

	if (**saveptr != '\0')
	{
		**saveptr = '\0';
		(*saveptr)++;
	}

	return (tkn);
}
