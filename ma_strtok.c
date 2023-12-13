#include "shell.h"

/**
 * ma_strtok - custom strtok function using a while loop
 * @usrin: user input to be separated into strings
 * @separ: the separator (delimiter)
 *
 * Return: separated string
 */
char *ma_strtok(char *usrin, const char *separ)
{
	static char *str;
	char *str_copy = NULL;

	if (usrin != NULL)
		str = usrin;
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
