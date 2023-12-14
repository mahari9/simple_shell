#include "shell.h"

/**
 * ma_getline - Read input from stdin
 * Return: the input on a tmpso
 */
char *ma_getline()
{
	int i, read_line;
	char k = 0;
	static char *tmpso, *result;
	static int tmpsosize = TMPMAXSIZE;

	tmpso = malloc(tmpsosize);
	if (tmpso == NULL)
	{
		free(tmpso);
		return (NULL);
	}
	for (i = 0; k != EOF && k != '\n'; i++)
	{
		read_line = read(STDIN_FILENO, &k, 1);
		if (read_line == 0)
		{
			free(tmpso);
			exit(EXIT_SUCCESS);
		}
		tmpso[i] = k;
		if (tmpso[0] == '\n')
		{
			free(tmpso);
			return (NULL);
		}
		if (i >= tmpsosize)
		{
			tmpso = ma_realloc(tmpso, tmpsosize, (tmpsosize + 2));
			if (tmpso == NULL)
			{
				free(tmpso);
				return (NULL);
			}
		}
	}
	tmpso[i] = '\0';
	result = ma_process_line(tmpso);
	free(tmpso);
	return (result);
}

/**
 * ma_process_line - A line read from stdin to be processed
 * @line: user input
 * Return: the input on a tmpso
 */
char *ma_process_line(char *line)
{
	int i, j = 0;
	int line_len = ma_strlen(line);
	char *result;

	result = malloc(sizeof(char) * (line_len + 1));
	if (result == NULL)
	{
		free(line);
		free(result);
		return (NULL);
	}
	for (i = 0; line[i] == ' '; i++)
		;
	for (; line[i + 1] != '\0'; i++)
	{
		result[j] = line[i];
		j++;
	}
	result[j] = '\0';
	if (result[0] == '\0' || result[0] == '#')
	{
		free(line);
		return ("\0");
	}
	for (i = 0; result[i] != '\0'; i++)
	{
		if (result[i] == '#' && result[i - 1] == ' '
				&& result[i + 1] == ' ')
		{
			result[i] = '\0';
		}
	}
	return (result);
}

/**
 * validate_file - validate file regularity
 * @pn: path name to the file to be validated
 *
 * Return: 1 if a regular file 0 else
 */
int validate_file(const char *pn)
{
	struct stat valid;

	stat(pn, &valid);
	return (S_ISREG(valid.st_mode));
}
