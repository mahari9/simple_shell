#include "shell.h"

/**
 * ma_atoi - function that change string into integer
 * @str: string to be changed
 * Return: changed integer
 */
int ma_atoi(char *str)
{
	int sign = 1, i = 0;
	unsigned int result = 0;

	while (!(str[i] <= '9' && str[i] >= '0') && str[i] != '\0')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] <= '9' && (str[i] >= '0' && str[i] != '\0'))
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	result *= sign;
	return (result);
}

/**
 * ma_itoa - Function that converts integer to string
 * @num: num to be  converted to string
 *
 * Return: pointer to converted string
 */
char *ma_itoa(int num)
{
	int remain = num, i, digits = 0;
	char *str;

	while (remain != 0)
	{
		remain /= 10;
		digits++;
	}
	if (num == 0)
		digits = 1;
	str = malloc((digits + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	i = digits - 1;
	while (num > 0)
	{
		str[i] = '0' + (num % 10);
		num /= 10;
		i--;
	}
	str[digits] = '\0';
	return (str);
}

/**
*ma_puts - Function that write output of characters and strings
*@cos: character or string  to be written
*Return: 1 on success
*/
void ma_puts(char *cos)
{
	char nwlin = '\n';

	while (*cos != '\0')
	{
		write(1, cos, 1);
		cos++;
	}
	(void)nwlin;
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
			if (*hystk++ != *ndl++)
				break;
		if (!*ndl)
			return (r);
		ndl = n;
		r++;
		hystk = r;
	}
	return (0);
}

/**
 * signal_catcher - catch signal (Ctrl-C) interrupt from terminating the shell
 *
 * @sign_num: an integer that contains the signal number
 *
 * Return: nothing
 */

void signal_catcher(int sign_num)
{
	write(STDOUT_FILENO, "\n$ ", 3);
	(void) sign_num;
}
