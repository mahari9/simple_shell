#include "shell.h"

/**
 * ma_strdup - function that duplicate string
 * @str: string to be duplicated
 * Return: pointer to new string
 */
char *ma_strdup(const char *str)
{
	char *buffer;
	unsigned int i, j;

	if (str == NULL)
		return (NULL);

	for (i = 0; str[i] != '\0'; i++)
		;

	buffer = malloc(sizeof(char) * (i + 1));

	if (buffer == NULL)
		return (NULL);

	for (j = 0; *(str + j) != '\0'; j++)
		buffer[j] = str[j];
	buffer[j] = '\0';
	return (buffer);
}


/**
 * ma_strndup - function that copies at most n bytes of string
 * @str: string to be duplicated
 * @n: number of bytes
 * Return: pointer to new string
 */
char *ma_strndup(const char *str, size_t n)
{
	char *nw_str;
	size_t i, len = 0;

	while (len < n && str[len] != '\0')
		len++;

	nw_str = malloc(len + 1);
	if (nw_str != NULL)
	{
		for (i = 0; i < len; i++)
			nw_str[i] = str[i];

		nw_str[len] = '\0';
	}

	return (nw_str);
}

/**
 * ma_strchr - custom version of the strchr function
 * @str: string which may contain character
 * @crt: character to be searched inside the string
 *
 * Return: pointer to the first occurance of crt or NULL
*/
char *ma_strchr(const char *str, int crt)
{
	while (*str != '\0')
	{
		if (*str == crt)
			return ((char *)str);
		str++;
	}
	return (NULL);
}

/**
 * append_str - converts an integer to a string and appends to buffer
 * @buffer: buffer to which the string appended
 * @str: string o be appended
 * @n: integer to be convert (used if str is NULL)
 * @i: pointer to the current index inbuffer
 */
void append_str(char **buffer, char *str, int n, size_t *i)
{
        char *s = NULL;

        if (!str || n)
        {
                if (n != 0)
                {
                        s = ma_itoa(n);
                        if (!s)
                                return;
                }
                else
                        s = "0";
                if (!*buffer)
                {
                        ma_perror(NULL, 12);
                        return;
                }
                ma_strcpy(*buffer, s);
                *i += ma_strlen(s);
                if (n)
                        free(s);
        }
        else
        {
                if (!buffer)
                {
                        ma_perror(NULL, 12);
                        return;
                }
                ma_strcpy(*buffer, str);
                *i += ma_strlen(str);
                free(str);
        }
}
