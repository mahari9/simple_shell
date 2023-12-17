#include "shel.h"

/**
 * ma_strlen - Function for calculating the length of a string
 * @str: String to be calculate it's length
 * Return: length
 */
int ma_strlen(const char *str)
{
	int i = 0;
	int length = 0;

	while (str[i] != '\0')
	{
		length++;
		i++;
	}
	return (length);
}

/**
 * ma_strcpy - Function that copies string from src to dst
 * @dst: Pointer to destination
 * @src: Pointer to source
 * Return: *dst
 */
char *ma_strcpy(char *dst, char *src)
{
	int i, length;

	for (length = 0; src[length] != '\0'; length++)
		;
	for (i = 0; i <= length ; i++)
		dst[i] = src[i];
	return (dst);
}

/**
 * ma_strdup - function that duplicate string
 * @str: string to be duplicated
 * Return: pointer to new string
 */
char *ma_strdup(const char *str)
{
	char *tmpsto;
	unsigned int i = 0, j = 0;

	if (str == NULL)
		return (NULL);
	while (str[i] != '\0')
		i++;
	tmpsto = (char *)malloc(sizeof(char) * (i + 1));
	if (tmpsto == NULL)
		return (NULL);
	while (*(str + j) != '\0')
	{
		tmpsto[j] = str[j];
		j++;
	}
	tmpsto[j] = '\0';
	return (tmpsto);
}

/**
 * ma_strndup - function that copies at most n bytes of string
 * @str: string to be duplicated
 * @n: number of bytes
 * Return: pointer to new string
 */
char *ma_strndup(const char *str, size_t n)
{
	char *alloc_str;
	size_t i = 0, length = 0;

	do {
		if (length >= n || str[length] == '\0')
		{
			break;
		}
		length++;
	} while (1);
	alloc_str = (char *)malloc(length + 1);
	if (alloc_str != NULL)
	{
		for (i = 0; i < length; i++)
		{
			alloc_str[i] = str[i];
		}
		alloc_str[length] = '\0';
	}
	return (alloc_str);
}

/**
 * ma_strcat - Function that appends two strings
 * @dst: Pointer to destination
 * @src: Pointer to source
 * Return: *dst
 */
char *ma_strcat(char *dst, const char *src)
{
	int i = 0, j = 0;

	do {
		i++;
	} while (dst[i] != '\0');
	do {
		dst[i] = src[j];
		i++;
		j++;
	} while (src[j] != '\0');
	dst[i] = '\0';
	return (dst);
}
