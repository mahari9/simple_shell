#include "shell.h"

/**
 * ma_getline - read input from source stream.
 * @linept: pointer to the input line
 * @n: the n the size of bytes read from input
 * @fd: file descriptor
 *
 * Return: n read or -1 on failure
 */
ssize_t ma_getline(char **linept, size_t *n, int fd)
{
	size_t index = 0, nw_rd;
	char *nw_ln;
	int c;

	if (linept == NULL || n == NULL)
	{
		errno = EINVAL;
		return (-1);
	}
	if (*linept == NULL)
	{
		*linept = malloc(256);
		if (*linept == NULL)
			return (-1);
		*n = 256;
	}
	while ((c = ma_getc(fd)) != EOF)
	{
		if (index + 1 >= *n)
		{
			nw_rd = (*n) * 2;
			nw_ln = ma_realloc(*linept, *n, nw_rd);
			if (nw_ln == NULL)
				return (-1);
			*linept = nw_ln;
			*n = nw_rd;
		}
		(*linept)[index++] = c;
		if (c == '\n')
		{
			(*linept)[index] = '\0';
			return (index);
		}
	}
	if (index == 0)
		return (-1);
	(*linept)[index] = '\0';
	return (index);
}

/**
 * ma_getc - funtion that reads c character at a time from file
 * @fd: file descriptor
 *
 * Return: read character
 */
int ma_getc(int fd)
{
	static char buffer[BUFFMAXSIZE];
	static size_t index;
	static size_t rd;

	if (index >= rd)
	{
		fill_buffer(fd, buffer, &index, &rd);

		if (rd <= 0 || index >= rd)
			return (EOF);
	}
	return ((int)buffer[index++]);
}

/**
 * fill_buffer - fill buffer from fd if the index is greater than size
 * @fd: file descriptor
 * @buffer: buffer that store the file
 * @index: pointer that keep track the absolute position in buffer
 * @rd: the size of buffer in bytes to be get read
 */

void fill_buffer(int fd, char *buffer, size_t *index, size_t *rd)
{
	*index = 0;
	*rd = read(fd, buffer, BUFFMAXSIZE);
}

/**
 * hashtag_comm - remove comments in line after hashtag
 * @line: input to be treated
 *
 * Return: line without comments or null
 */
char *hashtag_comm(char *line)
{
	size_t rmn;
	char *index, *treated_line = NULL;

	if (*line == '#')
		return (NULL);
	index = ma_strchr(line, '#');
	if (index)
	{
		rmn = index - line;
		if (rmn > 0 && line[rmn - 1] == ' ')
		{
			treated_line = ma_strndup(line, rmn);
			treated_line[rmn] = '\0';
			track_address(treated_line);
			line = treated_line;
		}
	}
	return (line);
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

	if (stat(pn, &valid) != 0)
		return (0);

	return (S_ISREG(valid.st_mode));
}
