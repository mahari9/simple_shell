#include "shell.h"

/**
 * ma_strcat - Function that appends two strings
 * @dst: Pointer to destination
 * @src: Pointer to source
 * Return: *dst
 */

char *ma_strcat(char *dst, char *src)
{
	int i = 0, j = 0;

	while (dst[i] != '\0')
		i++;
	while (src[j] != '\0')
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst);
}


/**
 * ma_strcpy - Function that copies string from src to dst
 * @dst: Pointer to destination
 * @src: Pointer to source
 * Return: *dst
 */
char *ma_strcpy(char *dst, char *src)
{
	int i, len;

	for (len = 0; src[len] != '\0'; len++)
		;
	for (i = 0; i <= len ; i++)
		dst[i] = src[i];
	return (dst);
}

/**
 * ma_strcmp - Function that compares two strings
 * @str1: string one
 * @str2: string two
 * Return: 0 on success and -1 on failure
 */

int ma_strcmp(char *str1, char *str2)
{
	int result = 0;

	while (*str1 == *str2 && *str1 != '\0')
	{
		str1++;
		str2++;
	}
	if (str1 != str2)
		result = *str1 - *str2;

	return (result);
}

/**
 * ma_strncmp - Function that compares n number of char of two strings
 * @str1: string one
 * @str2: string two
 * @n: Number of
 * Return: 0 on success
 */

int ma_strncmp(const char *str1, const char *str2, size_t n)
{
	while (n > 0)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		if (*str1 == '\0')
			return (0);
		str1++;
		str2++;
		n--;
	}
	return (0);
}

/**
 * ma_strlen - Function for calculating the length of a string
 * @str: String to be calculate it's length
 * Return: length
 */
int ma_strlen(char *str)
{
	int i, len = 0;

	for (i = 0; str[i] != '\0'; i++)
		len++;
	return (len);
}
