#include "shell.h"
/**
 * ma_strcmp - Function that compares two strings
 * @str1: string one
 * @str2: string two
 * Return: 0 on success and -1 on failure
 */
int ma_strcmp(char *str1, char *str2)
{
	int i = 0;

	do {
		if (str1[i] != str2[i] || str1[i] == '\0')
		{
			if (str1[i] > str2[i])
			{
				return (1);
			}
			else if (str1[i] < str2[i])
			{
				return (-1);
			}
			return (0);
		}
		i++;
	} while (1);
}

/**
 * ma_strncmp - Function that compares n number of char of two strings
 * @str1: string one
 * @str2: string two
 * @n: Number of
 * Return: integer value
 */
int ma_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t i = 0;

	if (str1 == NULL)
		return (-1);

	while (i < n && str2[i] != '\0')
	{
		if (str1[i] != str2[i])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 * ma_isalpha - function to check if c is alphabet
 * @c: char to be checked to check
 * Return: 1 if true 0 if false
 */
int ma_isalpha(char c)
{
	if (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * ma_atoi - function that change string into integer
 * @str: string to be changed
 * Return: changed integer
 */
int ma_atoi(char *str)
{
	int i = 0, sign = 1, c;
	unsigned int n = 0;

	do {
		if (str[i] == '-')
		{
			sign *= -1;
		}
		c = str[i] - '0';
		if (n > 0 && !(c >= 0 && c <= 9))
			break;
		if (c >= 0 && c <= 9)
			n = n * 10 + c;
		i++;
	} while (str[i] != '\0');
	n *= sign;
	return (n);
}

/**
 * ma_strstr - function finds the first occurrence of the substring in ndl
 * @hystk: pointer to char in string
 * @ndl: pointer to char to be searched
 *
 * Return: 0
 */
char *ma_strstr(char *hystk, char *ndl)
{
	char *r = hystk, *n = ndl;

	while (*hystk)
	{
		while (*ndl)
		{
			if (*hystk++ != *ndl++)
				break;
		}
		if (!*ndl)
		{
			return (r);
		}
		ndl = n;
		r++;
		hystk = r;
	}
	return (0);
}
