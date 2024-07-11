#include "shell.h"

/**
 * impl_var - implement variable replacement
 * @cmnd: command to be modified and replace
 * Return: value on success or NULL on failure
 */
char *impl_var(char *cmnd)
{
	char *name, *tmp, *value = NULL, *cmndcopy = cmnd;

	if (cmnd[0] == '$')
	{
		name = ++cmnd;
		tmp = ma_getenv(name);
		if (tmp != NULL)
		{
			value = malloc(strlen(tmp) + 1);
			ma_strcpy(value, tmp);
			free(tmp);
			return (value);
		}
		free(tmp);
		return (update_var(cmndcopy));
	}
	return (NULL);
}

/**
 * update_var - replace and update variables
 * @cmnd: command to tested
 * Return: append string or NUll on failure
 */
char *update_var(char *cmnd)
{
	char *tmp, *cmndcopy = cmnd;
	size_t index = 0, verify = 0;
	pid_t pid;

	tmp = malloc(254);
	if (!tmp)
		return (NULL);
	while (*cmnd)
	{
		if (cmnd[0] == '$' && cmnd[1] == '$')
		{
			pid = getpid();
			append_str(&tmp, NULL, pid, &index);
			cmnd += 2;
			verify++;
		}
		else if (cmnd[0] == '$' && cmnd[1] == '?')
		{
			append_str(&tmp, NULL, exit_status, &index);
			cmnd += 2;
			verify++;
			}
		else
			tmp[index++] = *cmnd++;
	}
	tmp[index] = '\0';
	if (verify)
		return (tmp);
	if (cmndcopy[0] == '$' && cmndcopy[1])
		replflag = 1;
	free(tmp);
	return (NULL);
}
/**
 * append_str - converts an integer to a string and appends to buffer
 * @tmp: buffer to which the string appended
 * @str: string o be appended
 * @num: integer to be convert (used if str is NULL)
 * @i: pointer to the current index inbuffer
 */
void append_str(char **tmp, char *str, int num, size_t *i)
{
	char *istr = NULL;

	if (!str || num)
	{
		if (num != 0)
		{
			istr = ma_itoa(num);
			if (!istr)
				return;
		}
		else
			istr = "0";
		if (!*tmp)
		{
			ma_perror(NULL, 12);
			return;
		}
		ma_strcpy(*tmp, istr);
		*i += ma_strlen(istr);
		if (num)
			free(istr);
	}
	else
	{
		if (!tmp)
		{
			ma_perror(NULL, 12);
			return;
		}
		ma_strcpy(*tmp, str);
		*i += ma_strlen(str);
		free(str);
	}
}
