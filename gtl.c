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
	size_t index = 0, n_rd = 128, nw_rd;
	char *nw_ln;
	int c;

	if (linept == NULL || n == NULL)
	{
		errno = EINVAL;
		return (-1);
	}
	if (*linept == NULL)
	{
		*linept = (char*)malloc(n_rd);
		if (*linept == NULL)
			return (-1);
		*n = n_rd;
	}
	while ((c = ma_getc(fd)) != EOF)
	{
		if (index + 1 >= *n)
		{
			nw_rd = (*n) * 2;
			nw_ln = (char*)ma_realloc(*linept, *n, nw_rd);
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
